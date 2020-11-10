/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:59:26 by icanker           #+#    #+#             */
/*   Updated: 2020/11/10 16:00:25 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

int		check_room(char *line)
{
	int i;
	int space;

	i = 0;
	space = 0;
	if (line[0] == 'L')
		error_getrooms(line);
	while (line[i] != '\0')
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

int		check_line(char *line)
{
	if (line[0] == '#')
		return (1);
	return (check_room(line));
}

void	check_coords(t_lemin *lem)
{
	int i;
	int	j;

	i = 0;
	while (i < lem->num_rooms)
	{
		j = lem->num_rooms - 1;
		while (j > i)
		{
			if (lem->rooms[i].x == lem->rooms[j].x &&
				lem->rooms[i].y == lem->rooms[j].y)
				error_coord(lem, &lem->rooms[i], &lem->rooms[j]);
			j--;
		}
		i++;
	}
}
