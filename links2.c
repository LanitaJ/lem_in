/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:29:46 by icanker           #+#    #+#             */
/*   Updated: 2020/11/10 15:39:33 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

int		compare(t_lemin *lem, char *str)
{
	int i;
	int equil;

	i = 0;
	equil = 0;
	while (i != lem->num_rooms)
	{
		if (!ft_strcmp(lem->rooms[i].name, str))
			equil++;
		i++;
	}
	if (equil != 1)
		error_link(str);
	return (equil);
}

int		altor(t_lemin *lem)
{
	int i;
	int j;

	i = 0;
	while (i != lem->num_rooms)
	{
		lem->rooms[i].num_links = 0;
		j = 0;
		while (j != lem->num_links)
		{
			if ((!ft_strcmp(lem->rooms[i].name, lem->links[j].name1))
				|| (!ft_strcmp(lem->rooms[i].name, lem->links[j].name2)))
				create_link(&lem->rooms[i], &lem->links[j], lem);
			j++;
		}
		i++;
	}
	i = 0;
	while (i != lem->num_links)
	{
		free(lem->links[i].name1);
		free(lem->links[i++].name2);
	}
	return (1);
}

void	get_link(char *line, t_link *l, t_lemin *lem)
{
	if (!get_first_room(line, l))
		error_link(line);
	if (!get_second_room(ft_strchr(line, '-'), l))
		error_link(line);
	if (!(compare(lem, l->name1) * compare(lem, l->name2)))
		error_link(line);
}

int		add_link(t_lemin *lem, char *line)
{
	t_link		*tmp;
	int			i;

	i = -1;
	tmp = (t_link*)ft_memalloc(sizeof(t_link) * ++(lem->num_links));
	if (tmp == NULL)
		error_malloc();
	while (++i != lem->num_links - 1)
		tmp[i] = lem->links[i];
	get_link(line, &tmp[i], lem);
	free(lem->links);
	free(line);
	lem->links = tmp;
	return (1);
}

int		check_dblinks(t_lemin *lem)
{
	int i;
	int j;

	i = 0;
	while (i != lem->num_links - 1)
	{
		j = i;
		while (j++ < lem->num_links - 1)
		{
			if ((!strcmp(lem->links[i].name1, lem->links[j].name2) &&
				!strcmp(lem->links[i].name2, lem->links[j].name1)) ||
				(!strcmp(lem->links[i].name2, lem->links[j].name2) &&
				!strcmp(lem->links[i].name1, lem->links[j].name1)))
			{
				ft_printf(RED"Error double links"RST);
				exit(1);
			}
		}
		i++;
	}
	return (1);
}
