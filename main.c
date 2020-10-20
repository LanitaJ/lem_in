#include "includes/lemin.h"

//разряд инта !!!пример 1234 - разряд 4
int numlen(int nbr)
{
	int	res;

	res = 1;
	if (nbr / 10 >= 1)
		return (numlen(nbr / 10) + res);
	else
		return (res);
}

//чек на имя комнаты
int check_room(char* line)
{
	int i;
	int space;

	i = 0;
	space = 0;
	while(line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			if (line[i + 1] != ' ')
				space++;
		}
		i++;
	}
	return (space == 2) ? 1 : 0;
}

//проверить комнату
/*
ljerk:
думаю стоит сделать более "гибкую" проверку
(когда есть отступы в начале строки, пробелы в конце или между значениями)
*/
int check_line(char* line)
{
	if (line[0] == '#')
		return 1;
	return check_room(line);
}

//возвращает количество совпадений строки и комнат
int compare(t_lemin *lem, char* str)//return number of equivalent char* with rooms
{
	int i;
	int equil;

	i = 0;
	equil = 0;
	while(i != lem->num_rooms)
	{
		if(!ft_strcmp(lem->rooms[i].name, str))
			equil++;
		i++;
	}
	if (equil != 1)
	{
		ft_putstr("compare ");
		ft_putstr(str);
		exit(1);
	}
	return (equil);
}


//возвращает ссылку на комнату исходя из имени
t_room *name_to_room(char *name, t_lemin *lem)
{
	int i;

	i = 0;
	while(i != lem->num_rooms)
	{
		if(!ft_strcmp(lem->rooms[i].name, name))
			return &lem->rooms[i];
		i++;
	}
	ft_putstr("name_to_room\n");
	exit(1);
}

//добавить связующую комнату(по названию name_add) к основной комнате(main_roon)
int add_room_to_room(t_room *main_room, char* name_add, t_lemin* lem)
{
	t_room*	*tmp;
	int*	tmp_blocks;
	int		i;

	i = 0;
	tmp = (t_room* *)malloc(sizeof(t_room*) * ++main_room->num_links);
	tmp_blocks = (int*)malloc(sizeof(int) * main_room->num_links);
	while (i != main_room->num_links - 1)
	{
		tmp_blocks[i] = 0;
		tmp[i] = main_room->n_rooms[i];
		i++;
	}
	tmp_blocks[i] = 0;
	tmp[i] = name_to_room(name_add, lem);
	if (main_room->num_links != 1)
	{
		free(main_room->n_rooms);//дополнить чистку
		free(main_room->blocks);
	}
	main_room->blocks = tmp_blocks;
	main_room->n_rooms = tmp;
	return 1;
}

//добавить связи к комнатам
int altor(t_lemin *lem)//add links to rooms
{
	int i;
	int j;

	i = 0;
	while(i != lem->num_rooms)
	{
		lem->rooms[i].num_links = 0;
		j = 0;
		while(j != lem->num_links)
		{
			if((!ft_strcmp(lem->rooms[i].name, lem->links[j].name1)) || (!ft_strcmp(lem->rooms[i].name, lem->links[j].name2)))
					create_link(&lem->rooms[i], &lem->links[j], lem);
			j++;
		}
		i++;
	}
	return (1);
}

int parse_all(t_lemin *lem)
{
	char* line;

	get_next_line(lem->fd, &line);
	lem->num_ants = ft_atoi(line);
	free(line);
	//ft_printf("%d", lem->num_ants);
	get_links(lem, get_rooms(lem,line));
	if ((!lem->id_start_room && lem->id_start_room != 0) || (!lem->id_end_room && lem->id_end_room != 0))
	{
		ft_putstr("start and end room\n");
		exit(1);
	}
	lem->start_room = &(lem->rooms[lem->id_start_room]);
	lem->end_room = &lem->rooms[lem->id_end_room];
	return 1;
}

void init_lemin(t_lemin *lem, int ac, char **av)
{
	if (ac == 2)
	{
		av++;
		lem->fd = open(av[0], O_RDONLY);
		if (lem->fd == -1)
			ft_printf("input error\n");
	}
	else
		lem->fd = 0;
	lem->num_rooms = 0;
	lem->num_links = 0;
	lem->check_end_kol = 0;
	lem->check_start_kol = 0;
}

//функция вывода карты в консоль (Вспомогательная функция. После окончания проекта удалить)
void	output_map(t_lemin lem)
{
	int i = 0;
	int j = 0;
	while(i < lem.num_rooms)
	{
		ft_printf("\nroom[%d] = %s\n", i, lem.rooms[i].name);
		j = 0;
		ft_printf("links: ");
		while (j < lem.rooms[i].num_links)
		{
			ft_printf("%s ", lem.rooms[i].n_rooms[j]->name);
			j++;
		}
		j = 0;
		ft_printf("blocks: ");
		while (j < lem.rooms[i].num_links)
		{
			ft_printf("%d ", lem.rooms[i].blocks[j]);
			j++;
		}
		ft_printf("\n-------------------\n");
		i++;
	}
}

int main(int ac, char **av)
{
	t_lemin lem;
  
	init_lemin(&lem, ac, av);
	parse_all(&lem);
	/*int i = 0;
	 ft_printf("num_ants %d", lem.num_ants);
	while(i != lem.num_rooms)
	{
		ft_printf("%s %d %d\n", lem.rooms[i].name, lem.rooms[i].x, lem.rooms[i].y);
		i++;
	}
	ft_printf("%s %d %d\n", lem.start_room->name, lem.start_room->x, lem.start_room->y);
	ft_printf("%s %d %d\n", lem.end_room->name, lem.end_room->x, lem.end_room->y);
	
 	int j = 0;
 	while(j != lem.num_links)
	{
		ft_printf("%s-%s\n", lem.links[j].name1, lem.links[j].name2);
		j++;
	} */
	altor(&lem);
 /* 	t_room *room;
 	int i = 0;
 	ft_putstr(lem.start_room->name);
 	ft_putchar('\n');
 	ft_putnbr(lem.start_room->num_links);
	ft_putchar('\n');
 	while(i != lem.start_room->num_links)
	{
 		room = lem.start_room->n_rooms[i];
 		ft_putstr(lem.start_room->name);
 		ft_putchar('-');
 		ft_putstr(room->name);
		ft_putchar(' ');
 		i++;
	}
	ft_putchar('\n'); */
	//вывод 
	output_map(lem);
	find_pathes(&lem);
	return (0);
}
