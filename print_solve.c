/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:10:27 by icanker           #+#    #+#             */
/*   Updated: 2020/11/10 14:10:33 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

void			count_aunts_for_pathes(t_path **pathes, t_lemin *lem)
{
	int i;

	i = 0;
	while (i < lem->ins)
		pathes[i++]->count_ants = 0;
	while (1)
	{
		i = 0;
		if (i == lem->ins)
			return ;
		while (i != lem->ins)
		{
			if (lem->usable_aunts >= lem->num_ants)
				return ;
			if (pathes[i]->length + pathes[i]->count_ants
				< lem->stage)
			{
				pathes[i]->count_ants++;
				lem->usable_aunts++;
			}
			i++;
		}
		lem->stage++;
	}
}

t_room			*findnext(t_path *path, t_room *this_room)
{
	int i;

	i = 0;
	while (i != path->length - 1)
	{
		if (!strcmp(path->sh[i]->name, this_room->name))
			return (path->sh[i + 1]);
		i++;
	}
	return (this_room);
}

int				count_iterations(t_lemin *lem, t_path **pathes)
{
	int i;
	int max;

	i = 0;
	max = -1;
	while (i != lem->ins)
	{
		if (max < pathes[i]->length - 1 + pathes[i]->count_ants && \
				pathes[i]->count_ants != 0)
			max = pathes[i]->length - 1 + pathes[i]->count_ants;
		i++;
	}
	return (max);
}

static	void	do_iteration(int *j, t_lemin *lem, t_path **pathes, int *a_i)
{
	while (lem->ants[*a_i].visited_room && *a_i <= lem->num_ants - 1)
	{
		if (ft_strcmp(lem->ants[*a_i].visited_room->name, lem->end_room->name))
		{
			lem->ants[*a_i].visited_room = findnext(lem->ants[*a_i].used_path,
				lem->ants[*a_i].visited_room);
			print_color_solve(lem, a_i);
		}
		(*a_i)++;
	}
	*j = 0;
	while (*j != lem->ins && *a_i <= lem->num_ants - 1)
	{
		if (pathes[*j]->count_ants > 0)
		{
			lem->ants[*a_i].used_path = pathes[*j];
			lem->ants[*a_i].visited_room = pathes[*j]->sh[1];
			pathes[*j]->count_ants -= 1;
			print_color_solve(lem, a_i);
			(*a_i)++;
		}
		(*j)++;
	}
}

void			print_solve(t_lemin *lem, t_path **pathes)
{
	int i;
	int max;
	int j;
	int a_i;

	max = count_iterations(lem, pathes);
	i = 0;
	while (i != max)
	{
		a_i = 0;
		ft_putstr("\n");
		do_iteration(&j, lem, pathes, &a_i);
		i++;
	}
	if (lem->num_lines == 1)
		lem->color ? ft_printf(GRN"Count of lines: %d\n"RST, max) : \
						ft_printf("Count of lines: %d\n", max);
}
