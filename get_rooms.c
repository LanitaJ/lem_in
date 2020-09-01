/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerk <ljerk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:34:06 by ljerk             #+#    #+#             */
/*   Updated: 2020/09/01 17:36:54 by ljerk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

int get_room(char* line, t_room *room)
{
	int i;

	i = 0;
	while(line[i] != '\0')
	{
		if(line[i] == ' ')
		{
			room->name = ft_strnew(i);
			room->name = ft_strtrim(line);
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

int add_room(t_lemin *lem, char* line)
{
	t_room* tmp;
	int i = -1;

	tmp = (t_room*)malloc(sizeof(t_room) * ++(lem->num_rooms));
	while(++i != lem->num_rooms - 1)
		tmp[i] = lem->rooms[i];
	get_room(line, &tmp[i]);
	free(lem->rooms);
	free(line);
	lem->rooms = tmp;
	return (1);
}


void exit_get_room(char* line)
{
	if (!check_room(line))
	{
		ft_putstr("get_room");
		exit(1);
	}
}

void get_rooms(t_lemin *lem)
{
	char *line;

	while(get_next_line(lem->fd, &line) > 0 && check_line(line))
	{
		//ft_printf("%s\n", line);
		lem->start_room.name = ft_strtrim(line);
		ft_printf("%s\n", lem->start_room.name);
		/* if (!ft_strcmp(line, "##start"))
		{
			get_next_line(lem->fd, &line);
			exit_get_room(line);
			get_room(line, &lem->start_room);
			free(line);
		}
		else if (!ft_strcmp(line, "##end"))
		{
			get_next_line(lem->fd, &line);
			exit_get_room(line);
			get_room(line, &lem->end_room);
			free(line);
		}
		else if (line[0] == '#') {
			free(line);
		}
		else
		{
			add_room(lem, line);
			free(line);
		}	 */
	}
	//return line;
}

int get_first_room(char* line, t_link *l)
{
	int i;
	int len = 0;
	//char *c;

	i = 0;
	while(line[i] != '\0')
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
			return 1;
		}
		i++;
	}
	return 0;
}

int get_second_room(char *line, t_link *l)
{
	int		i;
	int		len;

	len = (int)(ft_strlen(line) - 1);
	l->name2 = ft_strnew(len);
	i = 0;
	while(i != len)
	{
		l->name2[i] = line[i + 1];
		i++;
	}
	return (1);
}