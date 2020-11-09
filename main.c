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

void		init_id(t_lemin *lem)
{
	int	id;

	id = 0;
	while (id < lem->num_rooms)
	{
		lem->rooms[id].id = id;
		id++;
	}
}

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
	return (ft_atoi(line));
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
		error_malloc();
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
	ft_printf("%s\n", line);
	lem->num_ants = get_aunts(line);
	free(line);
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
	else if (ac > 2)
		error_count_args();
	else
		lem->fd = 0;
	lem->num_rooms = 0;
	lem->num_links = 0;
	lem->check_end_kol = 0;
	lem->check_start_kol = 0;
}

void count_aunts_for_pathes(t_path* *mass_pathes, t_lemin *lem)
{
	int stage;
	int UsableAunts;
	int i;

	UsableAunts = 0;
	stage = 1;
	i = 0;
	while(i < lem->ins)
		mass_pathes[i++]->count_ants = 0;
	while (1)
	{
		i = 0;
		if (i == lem->ins)
			return ;
		while(i != lem->ins)
		{
			if (UsableAunts >= lem->num_ants)
				return ;
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
	int i;

	i = 0;
	while (i != path->length - 1)
	{
		if (!strcmp(path->sh[i]->name, ThisRoom->name))
			return (path->sh[i + 1]);
		i++;
	}
	return (ThisRoom);
}

int count_iterations(t_lemin *lem, t_path* *mass_pathes)
{
	int i;
	int max;

	i = 0;
	max = -1;
	while (i != lem->ins)
	{
		if (max < mass_pathes[i]->length - 1 + mass_pathes[i]->count_ants && \
				mass_pathes[i]->count_ants != 0)
			max = mass_pathes[i]->length - 1 + mass_pathes[i]->count_ants;
		i++;
	}
	//ft_printf("max %d\n", max);
	return (max);
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
	ft_bzero(lem->ants, sizeof(lem->ants));
	while (i != max)
	{
		ft_putstr("\n");
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
		i++;
	}
	//ft_printf("i = %d\n", i);
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

void	free_mass_pathes(t_path **mas, t_lemin *lem)
{
	int	i;

	i = 0;
	while (i < lem->ins)
	{
		free(mas[i]->sh);
		//free(mas[i]->length);
		free(mas[i]);
		i++;
	}
	free(mas);
}

int main(int ac, char **av)
{
	t_lemin lem;
	t_path	**mass_pathes;

	if (ac == 3)
	{
		parse_flags(av, &lem);
		av++;
		ac--;
	}
	init_lemin(&lem, ac, av);
	parse_all(&lem);
	altor(&lem);
	init_id(&lem);
	check_coords(&lem);
	mass_pathes = find_pathes(&lem);
	if (lem.show_path == 1)
		show_pathes(lem, mass_pathes);
	count_aunts_for_pathes(mass_pathes, &lem);
	Run(&lem, mass_pathes);
	free_mass_pathes(mass_pathes, &lem);
	free_lemin(&lem);
	return (0);
}
