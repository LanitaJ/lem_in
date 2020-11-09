/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerk <ljerk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:35:05 by ljerk             #+#    #+#             */
/*   Updated: 2020/09/04 20:37:31 by ljerk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

//является ли связь валидной
int		check_link(char *line)
{
	//написать:
	//парсинг 1го и 2го имени, проверка существования комнаты
	if (line[1] == '-')
		return (1);

	return (0);
}

//получить название первой комнаты из линка !!!например: 1-2 => записываем комнату 1
int get_first_room(char* line, t_link *l)
{
	int i;
	int len;

	len = 0;
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
			return (1);
		}
		i++;
	}
	return (0);
}
//получить название второй комнаты из линка !!!например: 1-2 => записываем комнату 2
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

//записать связь в основную струкутуру
void get_link(char* line, t_link *l, t_lemin *lem)
{
	if(!get_first_room(line, l))
		error_link(line);
	if(!get_second_room(ft_strchr(line, '-'), l))
		error_link(line);
	if (!(compare(lem, l->name1) * compare(lem, l->name2)))
		error_link(line);
}

//добавить связь к существующем с ежевызываемым удалением
int add_link(t_lemin *lem, char* line)
{
	t_link* tmp;
	int i = -1;

	tmp = (t_link*)ft_memalloc(sizeof(t_link) * ++(lem->num_links));
	if (tmp == NULL)
		error_malloc();
	while(++i != lem->num_links - 1)
		tmp[i] = lem->links[i];
	get_link(line, &tmp[i], lem);
	free(lem->links);
	free(line);
	lem->links = tmp;
	return (1);
}

//проверка на наличие дублирующих линков
int check_dblinks(t_lemin *lem)
{
	int i;
	int j;

	i = 0;
	while(i != lem->num_links - 1)
	{
		j = i;
		while(j++ < lem->num_links - 1)
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

//записать связи в основную струкутуру
int get_links(t_lemin *lem, char *line)
{
	int i;

	i = 0;
	add_link(lem, line);
	while(get_next_line(lem->fd, &line))
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

//передать ссылки на соседние комнаты
int create_link(t_room *main_room, t_link *link, t_lemin *lem)
{
	if (!ft_strcmp(main_room->name, link->name1))
		add_room_to_room(main_room, link->name2, lem);
	else
		add_room_to_room(main_room, link->name1, lem);
	return (1);
}