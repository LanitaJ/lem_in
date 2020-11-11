/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:58:57 by icanker           #+#    #+#             */
/*   Updated: 2020/11/11 12:59:01 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

void	free_path(t_path *path)
{
	free(path->sh);
	free(path);
}

void	free_mass_pathes(t_path **mas, t_lemin *lem)
{
	int	i;

	i = 0;
	while (i < lem->ins)
	{
		free(mas[i]->sh);
		free(mas[i]);
		i++;
	}
	free(mas);
}

void	free_main_room(t_room *main_room)
{
	free(main_room->n_rooms);
	free(main_room->blocks);
}

void	free_lemin(t_lemin *lem)
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
