/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerk <ljerk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:35:05 by ljerk             #+#    #+#             */
/*   Updated: 2020/09/01 19:45:54 by ljerk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"


int		check_link(char *line)
{
	//написать:
	//парсинг 1го и 2го имени, проверка существования комнаты
	if (line[1] == '-')
		return (1);
	return (0);
}

void get_link(char* line, t_link *l, t_lemin *lem)
{

	if(!get_first_room(line, l))
	{
		ft_putstr("get_link ");
		ft_putstr(line);
		exit(0);
	}
	if(!get_second_room(ft_strchr(line, '-'),l))
	{
		ft_putstr("get_link ");
		ft_putstr(line);
		exit(0);
	}
	if (!(compare(lem,l->name1) * compare(lem,l->name2)))
	{
		ft_putstr("compare ");
		ft_putstr(line);
		exit(0);
	}
}

int add_link(t_lemin *lem, char* line)
{
	t_link* tmp;
	int i = -1;

	tmp = (t_link*)malloc(sizeof(t_link) * ++(lem->num_links));
	while(++i != lem->num_links - 1)
		tmp[i] = lem->links[i];
	get_link(line, &tmp[i], lem);
	if (lem->num_links != 1)
		free(lem->links);
	free(line);
	lem->links = tmp;
	return 1;
}

int get_links(t_lemin *lem, char *line)
{
	int i;

	i = 0;
	add_link(lem, line);
	while(get_next_line(0, &line))
		add_link(lem, line);
	return (1);
}

int create_link(t_room *main_room, t_link *link, t_lemin *lem)
{
	if (!ft_strcmp(main_room->name, link->name1))
		add_room_to_room(main_room, link->name2, lem);
	else
		add_room_to_room(main_room, link->name1, lem);
	return 1;
}