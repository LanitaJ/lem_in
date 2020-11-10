/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:35:05 by ljerk             #+#    #+#             */
/*   Updated: 2020/11/10 15:26:55 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

int	get_first_room(char *line, t_link *l)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '-')
		{
			len = i;
			l->name1 = ft_strnew(i);
			i = 0;
			while (i != len)
			{
				l->name1[i] = line[i];
				i++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_second_room(char *line, t_link *l)
{
	int		i;
	int		len;

	len = (int)(ft_strlen(line) - 1);
	l->name2 = ft_strnew(len);
	i = 0;
	while (i != len)
	{
		l->name2[i] = line[i + 1];
		i++;
	}
	return (1);
}

int	get_links(t_lemin *lem, char *line)
{
	int i;

	i = 0;
	add_link(lem, line);
	while (get_next_line(lem->fd, &line))
	{
		ft_putstr(line);
		ft_putstr("\n");
		if (line[0] == '#')
			free(line);
		else
			add_link(lem, line);
	}
	return (check_dblinks(lem));
}

int	create_link(t_room *main_room, t_link *link, t_lemin *lem)
{
	if (!ft_strcmp(main_room->name, link->name1))
		add_room_to_room(main_room, link->name2, lem);
	else
		add_room_to_room(main_room, link->name1, lem);
	return (1);
}
