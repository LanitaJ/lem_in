/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:12:21 by icanker           #+#    #+#             */
/*   Updated: 2020/11/10 15:56:45 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

void	help_do_iteration(t_lemin *lem)
{
	char *line;

	get_next_line(lem->fd, &line);
	ft_printf("%s\n", line);
	exit_get_room(line);
	add_room(lem, line);
}

int		numlen(int nbr)
{
	int	res;

	res = 1;
	if (nbr / 10 >= 1)
		return (numlen(nbr / 10) + res);
	else
		return (res);
}

t_room	*name_to_room(char *name, t_lemin *lem)
{
	int i;

	i = 0;
	while (i != lem->num_rooms)
	{
		if (!ft_strcmp(lem->rooms[i].name, name))
			return (&lem->rooms[i]);
		i++;
	}
	ft_putstr("name_to_room\n");
	exit(1);
}

int		add_room_to_room(t_room *main_room, char *name_add, t_lemin *lem)
{
	t_room	**tmp;
	int		*tmp_blocks;
	int		i;

	i = 0;
	main_room->num_links++;
	tmp = (t_room**)malloc(sizeof(t_room*) * main_room->num_links);
	tmp_blocks = (int*)malloc(sizeof(int) * main_room->num_links);
	if (tmp == NULL || tmp_blocks == NULL)
		error_malloc();
	while (i != main_room->num_links - 1)
	{
		tmp_blocks[i] = 0;
		tmp[i] = main_room->n_rooms[i];
		i++;
	}
	tmp_blocks[i] = 0;
	tmp[i] = name_to_room(name_add, lem);
	if (main_room->num_links != 1)
		free_main_room(main_room);
	main_room->blocks = tmp_blocks;
	main_room->n_rooms = tmp;
	return (1);
}
