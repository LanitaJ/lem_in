/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:11:36 by icanker           #+#    #+#             */
/*   Updated: 2020/11/10 16:11:38 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

static	int	get_aunts(char *line)
{
	int	i;

	i = 0;
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

<<<<<<< HEAD
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
=======
int			parse_all(t_lemin *lem)
>>>>>>> 08cbd88b2d060af364cce5b7bc4cfda238c7049a
{
	char	*line;

	get_next_line(lem->fd, &line);
	ft_printf("%s\n", line);
	lem->num_ants = get_aunts(line);
	free(line);
	get_links(lem, get_rooms(lem, line));
	if ((!lem->id_start_room && lem->id_start_room != 0) ||
		(!lem->id_end_room && lem->id_end_room != 0))
		error_start_end();
	lem->start_room = &(lem->rooms[lem->id_start_room]);
	lem->end_room = &lem->rooms[lem->id_end_room];
	init_ants(lem);
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
	lem->UsableAunts = 0;
	lem->stage = 1;
	lem->num_rooms = 0;
	lem->num_links = 0;
	lem->check_end_kol = 0;
	lem->check_start_kol = 0;
}

int main(int ac, char **av)
{
	t_lemin	lem;
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
	if (isolated(lem.start_room))
		error_isolated_start(&lem);
	mass_pathes = find_pathes(&lem);
	if (lem.show_path == 1)
		show_pathes(lem, mass_pathes);
	count_aunts_for_pathes(mass_pathes, &lem);
	print_solve(&lem, mass_pathes);
	free_mass_pathes(mass_pathes, &lem);
	free_lemin(&lem);
	return (0);
}
