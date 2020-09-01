#include "includes/lemin.h"

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
		else if (!ft_isdigit(line[i]))
			return 0;
		i++;
	}
	return (space == 2) ? 1 : 0;
}

int check_line(char* line)
{
	if (line[0] == '#')
		return (1);
	return check_room(line);
}

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
	equil += (!ft_strcmp(lem->start_room.name, str)) + (!ft_strcmp(lem->end_room.name, str));
	if (equil != 1)
	{
		ft_putstr("compare ");
		ft_putstr(str);
		exit(1);
	}
	return (equil);
}



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
	if(!ft_strcmp(lem->start_room.name, name))
		return &lem->start_room;
	if(!ft_strcmp(lem->end_room.name, name))
		return &lem->end_room;
	ft_putstr("name_to_room\n");
	exit(1);
}

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

/*
	парсинг карты:
					обработка всех ошибок
					считывание количества муравьев
					считывание старта/конца
					считывание комнаты
					считывание связи
					игнорирование комментариев и невалидных строк
	
	Добавить обработку:
						связи должны идти после(!) комнат.
						То есть после комнат могут быть только связи(новых комнат не может быть)
*/
void parse_map(t_lemin *lem)
{
	char *line;

	get_next_line(lem->fd, &line);
	lem->num_ants = ft_atoi(line);
	if (lem->num_ants < 0 && lem->num_ants > 2147483647)
		error_ant_count(line);
	ft_printf("%d\n", lem->num_ants);
	while (get_next_line(lem->fd, &line) > 0)
	{
		//возможно вставить free(line) в команды (чтобы сократить количество строк)
		if (ft_strequ("##start", line))
		{
			free(line);
			ft_printf("here_start\n");
			//parse_start();
		}
		else if (ft_strequ("##end", line))
		{
			free(line);
			ft_printf("end\n");
			//parse_end();
		}
		else if (check_link(line))
			ft_printf("link\n");
			//parse_link();
		else if (check_room(line))
			ft_printf("room\n");
			//parse_room();
		else if (ft_strchr(line, '#'))
			free(line);
		else
			error_trash(line);
	}
}

void init_lemin(t_lemin *lem, int ac, char **av)
{
	if (ac == 2)
	{
		av++;
		lem->fd = open(av[0], O_RDONLY);
		if (lem->fd == -1)
			ft_printf("input error");
	}
	else
		lem->fd = 0;
	//ft_printf("%d", lem->fd);
	lem->num_rooms = 0;
	lem->num_links = 0;
}

int main(int ac, char **av)
{
	t_lemin lem;

	//ft_printf("%d %s",ac, av[0]);
	init_lemin(&lem, ac, av);
	parse_map(&lem);
	/* int i = 0;
	ft_printf("%d", lem.num_ants);
	while(i != lem.num_rooms)
	{
		ft_printf("%s %d %d\n", lem.rooms[i].name, lem.rooms[i].x, lem.rooms[i].y);
		i++;
	}
	ft_printf("%s %d %d\n", lem.start_room.name, lem.start_room.x, lem.start_room.y);
	ft_printf("%s %d %d\n", lem.end_room.name, lem.end_room.x, lem.end_room.y);
	
 	int j = 0;
 	while(j != lem.num_links)
	{
		ft_printf("%s-%s\n", lem.links[j].name1, lem.links[j].name2);
		j++;
	}
	altor(&lem);

 	t_room *room;
 	i = 0;
 	ft_putstr(lem.rooms[3].name);
 	ft_putchar('\n');
 	while(i != lem.rooms[3].num_links)
	{
 		room = lem.rooms[3].n_rooms[i];
 		ft_putnbr(lem.rooms[3].blocks[i]);
 		ft_putchar('-');
 		ft_putstr(room->name);
		ft_putchar(' ');

 		i++;
	} */
	return (0);
}
