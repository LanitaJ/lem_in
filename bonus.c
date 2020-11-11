/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:53:46 by icanker           #+#    #+#             */
/*   Updated: 2020/11/11 12:53:51 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

void		parse_flags(char **av, t_lemin *lem)
{
	int i;

	lem->bonus = 0;
	i = 1;
	if (av[1][0] == '-')
		while (av[1][i] != '\0')
		{
			if (av[1][i] == 'c')
				lem->color = 1;
			else if (av[1][i] == 'p')
				lem->show_path = 1;
			else if (av[1][i] == 'n')
				lem->num_lines = 1;
			i++;
		}
	if (lem->color == 1 || lem->show_path == 1 || lem->num_lines == 1)
		lem->bonus = 1;
}

void		print_path(t_path *path)
{
	int i;

	i = 0;
	while (i < path->length)
	{
		if (i != path->length - 1)
			ft_printf("%s->", path->sh[i]->name);
		else
			ft_printf("%s\n", path->sh[i]->name);
		i++;
	}
}

void		print_path_color(t_path *path)
{
	int i;

	i = 0;
	while (i < path->length)
	{
		if (i != path->length - 1 && i % 2 == 0 && i % 4 != 0 && i % 6 != 0)
			ft_printf(RED"%s->"RST, path->sh[i]->name);
		else if (i != path->length - 1 && i % 3 == 0 && i % 6 != 0)
			ft_printf(GRN"%s->"RST, path->sh[i]->name);
		else if (i != path->length - 1 && i % 4 == 0)
			ft_printf(YEL"%s->"RST, path->sh[i]->name);
		else if (i != path->length - 1 && i % 5 == 0)
			ft_printf(BLU"%s->"RST, path->sh[i]->name);
		else if (i != path->length - 1 && i % 6 == 0)
			ft_printf(MAG"%s->"RST, path->sh[i]->name);
		else if (i != path->length - 1 && i % 7 == 0)
			ft_printf(CYN"%s->"RST, path->sh[i]->name);
		else if (i != path->length - 1)
			ft_printf(CYN"%s->"RST, path->sh[i]->name);
		else if (i == path->length - 1)
			ft_printf("%s\n", path->sh[i]->name);
		i++;
	}
}

void		show_pathes(t_lemin lem, t_path **mass_pathes)
{
	int	i;

	i = 0;
	while (i < lem.ins)
	{
		if (lem.color == 1)
			ft_printf(CYN"Chain #%d:\n"RST, i + 1);
		else
			ft_printf("Chain #%d:\n", i + 1);
		if (lem.color == 1)
			print_path_color(mass_pathes[i]);
		else
			print_path(mass_pathes[i]);
		i++;
	}
}

void		print_color_solve(t_lemin *lem, int *a_i)
{
	if (lem->color == 1)
	{
		if (*a_i % 2 == 0 && *a_i % 4 != 0 && *a_i % 6 != 0)
			ft_printf(RED"L%d-%s "RST, lem->ants[*a_i].nbr,\
				lem->ants[*a_i].VisitedRoom->name);
		else if (*a_i % 3 == 0 && *a_i % 6 != 0)
			ft_printf(GRN"L%d-%s "RST, lem->ants[*a_i].nbr,\
				lem->ants[*a_i].VisitedRoom->name);
		else if (*a_i % 4 == 0)
			ft_printf(CYN"L%d-%s "RST, lem->ants[*a_i].nbr,\
				lem->ants[*a_i].VisitedRoom->name);
		else if (*a_i % 5 == 0)
			ft_printf(BLU"L%d-%s "RST, lem->ants[*a_i].nbr,\
				lem->ants[*a_i].VisitedRoom->name);
		else if (*a_i % 6 == 0)
			ft_printf(MAG"L%d-%s "RST, lem->ants[*a_i].nbr,\
				lem->ants[*a_i].VisitedRoom->name);
		else
			ft_printf(YEL"L%d-%s "RST, lem->ants[*a_i].nbr,\
				lem->ants[*a_i].VisitedRoom->name);
	}
	else
		ft_printf("L%d-%s ", lem->ants[*a_i].nbr,\
			lem->ants[*a_i].VisitedRoom->name);
}
