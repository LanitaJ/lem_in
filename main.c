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
	if (line[0] == 'L')
		error_getrooms(line);
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

void InitAnts(t_lemin *lem)
{
	int i;

	lem->ants = (t_ant *)malloc(sizeof(t_ant) * lem->num_ants);
	i = 1;
	while (i != lem->num_ants + 1)
	{
		lem->ants[i - 1].nbr = i;
		lem->ants[i - 1].VisitedRoom = NULL;
		lem->ants[i - 1].UsedPath = NULL;
		i++;

	}
}

static int get_aunts(char* line)
{
	int i = 0;
	while (line[i] != '\0')
	{
		if (line[i] > '9' || line[i] < '0')
			error_ant_count(line);
		i++;
	}
	if (ft_atoi(line) <= 0)
		error_ant_count(line);
	return ft_atoi(line);
}

int check_line(char* line)
{
	if (line[0] == '#')
		return (1);
	return (check_room(line));
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
		error_link(str);
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
			return (&lem->rooms[i]);
		i++;
	}
	ft_putstr("name_to_room\n");
	exit(1);
}

static void free_main_room(t_room *main_room) //дополнить чистку
{
	free(main_room->n_rooms);
	free(main_room->blocks);
}

//добавить связующую комнату(по названию name_add) к основной комнате(main_roon)
int add_room_to_room(t_room *main_room, char* name_add, t_lemin* lem)
{
	t_room*	*tmp;
	int*	tmp_blocks;
	int		i;

	i = 0;
	main_room->num_links++;
	tmp = (t_room* *)malloc(sizeof(t_room*) * main_room->num_links);
	tmp_blocks = (int*)malloc(sizeof(int) * main_room->num_links);
	if (tmp == NULL || tmp_blocks == NULL)
		error_maloc();
	while (i != main_room->num_links - 1)
	{
		tmp_blocks[i] = 0;
		tmp[i] = main_room->n_rooms[i];
		i++;
	}
	tmp_blocks[i] = 0;
	tmp[i] = name_to_room(name_add, lem);
	if (main_room->num_links != 1)
		free_main_room(main_room);
	main_room->blocks = tmp_blocks;
	main_room->n_rooms = tmp;
	return (1);
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
	i  = 0;
	while(i != lem->num_links)
	{
		free(lem->links[i].name1);
		free(lem->links[i++].name2);
	}
	return (1);
}

int parse_all(t_lemin *lem)
{
	char* line;

	get_next_line(lem->fd, &line);
	ft_putstr(line);
	ft_putstr("\n");
	lem->num_ants = get_aunts(line);
	free(line);
	//ft_printf("%d", lem->num_ants);
	get_links(lem, get_rooms(lem,line));
	if ((!lem->id_start_room && lem->id_start_room != 0) || (!lem->id_end_room && lem->id_end_room != 0))
		error_start_end();
	lem->start_room = &(lem->rooms[lem->id_start_room]);
	lem->end_room = &lem->rooms[lem->id_end_room];
	InitAnts(lem);
	return (1);
}

void init_lemin(t_lemin *lem, int ac, char **av)
{
	if (ac == 2)
	{
		av++;
		lem->fd = open(av[0], O_RDONLY);
		if (lem->fd == -1)
			error_fd();
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

void count_aunts_for_pathes(t_path* *mass_pathes, t_lemin *lem)
{
	int stage;
	int UsableAunts;
	int i;

	UsableAunts = 0;
	stage = 1;
	while (1)
	{
		i = 0;
		while(i != lem->ins)
		{
			if (UsableAunts >= lem->num_ants)
				return;
			if (mass_pathes[i]->length + mass_pathes[i]->count_ants < stage)
			{
				mass_pathes[i]->count_ants++;
				UsableAunts++;
			}
			i++;
		}
		stage++;
	}
}

t_room *FindNext(t_path* path, t_room* ThisRoom)
{
	int i = 0;

	while (i != path->length - 1)
	{
		if (!strcmp(path->sh[i]->name, ThisRoom->name))
			return path->sh[i + 1];

		i++;
	}

	return ThisRoom;
}

int count_iterations(t_lemin *lem, t_path* *mass_pathes)
{
	int i = 0;
	int max;
	max = -1;
	while (i != lem->ins)
	{
		if (max < mass_pathes[i]->length - 1 + mass_pathes[i]->count_ants && mass_pathes[i]->count_ants != 0)
			max = mass_pathes[i]->length - 1 + mass_pathes[i]->count_ants;
		i++;
	}
	return max;
}

void Run(t_lemin *lem, t_path* *mass_pathes)
{
	int i;
	int max;
	int j;
	int ant_i;

	max = count_iterations(lem, mass_pathes);
	ant_i = 0;
	i = 0;
	while (i != max)
	{
		ant_i = 0;
		while(lem->ants[ant_i].VisitedRoom && ant_i <= lem->num_ants - 1)
		{
			if (ft_strcmp(lem->ants[ant_i].VisitedRoom->name,lem->end_room->name))
			{
				lem->ants[ant_i].VisitedRoom = FindNext(lem->ants[ant_i].UsedPath, lem->ants[ant_i].VisitedRoom);
				ft_printf("L%d-%s ", lem->ants[ant_i].nbr, lem->ants[ant_i].VisitedRoom->name);
			}
			ant_i++;
		}
		j = 0;
		while(j != lem->ins && ant_i <= lem->num_ants - 1)
		{
			if (mass_pathes[j]->count_ants > 0)
			{
				lem->ants[ant_i].UsedPath = mass_pathes[j];
				lem->ants[ant_i].VisitedRoom = mass_pathes[j]->sh[1];
				mass_pathes[j]->count_ants -= 1;
				ft_printf("L%d-%s ", lem->ants[ant_i].nbr, lem->ants[ant_i].VisitedRoom->name);
				ant_i++;
			}
			j++;
		}
		ft_putstr("\n");
		i++;
	}
	ft_putnbr(i);
}

void free_lemin(t_lemin *lem)
{
	int i;

	i = 0;
	free(lem->links);
	i = 0;
	while (i != lem->num_rooms)
	{
		free(lem->rooms[i].name);
		free_main_room(&lem->rooms[i]);
		i++;
	}
	free(lem->rooms);
	free(lem->ants);
}

int main(int ac, char **av)
{
	t_lemin lem;
	t_path	**mass_pathes;

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
	mass_pathes = find_pathes(&lem);
	int i = 0;
	lem.color = 0;
	//вывод всех путей в консоль
	while (i < lem.ins)
	{
		if (lem.color == 1)
			print_path_color(mass_pathes[i]);
		else
			print_path(mass_pathes[i]);
		//free(mass_pathes[i]);
		i++;
	}
	//ft_printf("ins %d\n", lem.ins);

	count_aunts_for_pathes(mass_pathes, &lem);

	Run(&lem, mass_pathes);
	free(mass_pathes);
	free_lemin(&lem);
	return (0);
}
