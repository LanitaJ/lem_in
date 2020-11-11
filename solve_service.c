/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_service.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:57:44 by icanker           #+#    #+#             */
/*   Updated: 2020/11/11 12:58:01 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

void	del_first_link(int id_isol_room, t_lemin *lem)
{
	int	i;

	i = 0;
	while (i < lem->start_room->num_links)
	{
		if (id_isol_room == lem->start_room->n_rooms[i]->id)
			lem->start_room->blocks[i] = 1;
		i++;
	}
}

void	restore_first_link(int id_restore_room, t_lemin *lem)
{
	int	i;

	i = 0;
	while (i < lem->start_room->num_links)
	{
		if (id_restore_room == lem->start_room->n_rooms[i]->id)
			lem->start_room->blocks[i] = 0;
		i++;
	}
}

int		isolated(t_room *room)
{
	int i;

	i = 0;
	while (i < room->num_links)
	{
		if (room->blocks[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

int		check_shortcut(t_lemin *lem)
{
	int	i;

	i = 0;
	while (i < lem->start_room->num_links)
	{
		if (lem->start_room->n_rooms[i]->id == lem->end_room->id)
			return (1);
		i++;
	}
	return (0);
}

t_path	**check_solution(t_lemin *lem, t_path **mass_pathes)
{
	if (lem->ins == 0)
	{
		ft_printf(RED"{fd}No solution\n"RST, 2);
		free_mass_pathes(mass_pathes, lem);
		free_lemin(lem);
		exit(1);
	}
	return (mass_pathes);
}
