/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:34:06 by ljerk             #+#    #+#             */
/*   Updated: 2020/11/10 15:52:17 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

int			get_room(char *line, t_room *room)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			room->name = ft_strnew(i);
			ft_strncpy(room->name, line, i);
			line += i + 1;
			room->x = ft_atoi(line);
			line += numlen(room->x);
			room->y = ft_atoi(line);
			return (1);
		}
		i++;
	}
	return (0);
}

int			add_room(t_lemin *lem, char *line)
{
	t_room	*tmp;
	int		i;

	i = -1;
	tmp = (t_room*)ft_memalloc(sizeof(t_room) * ++(lem->num_rooms));
	if (tmp == NULL)
		error_malloc();
	while (++i != lem->num_rooms - 1)
		tmp[i] = lem->rooms[i];
	get_room(line, &tmp[i]);
	free(lem->rooms);
	free(line);
	lem->rooms = tmp;
	return (1);
}

void		exit_get_room(char *line)
{
	if (!check_room(line))
		error_getrooms(line);
}

static void	do_iteration(char *line, t_lemin *lem)
{
	ft_printf("%s\n", line);
	if (!ft_strcmp(line, "##start"))
	{
		lem->check_start_kol++;
		lem->id_start_room = lem->num_rooms;
		free(line);
		help_do_iteration(lem);
	}
	else if (!ft_strcmp(line, "##end"))
	{
		lem->check_end_kol++;
		lem->id_end_room = lem->num_rooms;
		free(line);
		help_do_iteration(lem);
	}
	else if (line[0] == '#')
	{
		free(line);
	}
	else
		add_room(lem, line);
}

char		*get_rooms(t_lemin *lem, char *line)
{
	while (get_next_line(lem->fd, &line) && check_line(line))
		do_iteration(line, lem);
	if (lem->check_start_kol != 1 || lem->check_end_kol != 1)
		error_start_end();
	return (line);
}
