/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:01:52 by icanker           #+#    #+#             */
/*   Updated: 2020/11/10 16:02:29 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

void	init_id(t_lemin *lem)
{
	int	id;

	id = 0;
	while (id < lem->num_rooms)
	{
		lem->rooms[id].id = id;
		id++;
	}
}

void	init_ants(t_lemin *lem)
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

void	init_lemin(t_lemin *lem, int ac, char **av)
{
	if (ac == 2)
	{
		av++;
		lem->fd = open(av[0], O_RDONLY);
		if (lem->fd == -1)
			error_fd();
		if (lem->bonus == 0)
		{
			lem->color = 0;
			lem->num_lines = 0;
			lem->show_path = 0;
		}
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
