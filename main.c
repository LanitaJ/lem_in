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

static int	get_aunts(char *line)
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

int			parse_all(t_lemin *lem)
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

int			main(int ac, char **av)
{
	t_lemin	lem;
	t_path	**mass_pathes;

	if (ac == 3)
	{
		parse_flags(av, &lem);
		av++;
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
