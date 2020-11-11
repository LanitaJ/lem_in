/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerk <ljerk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 09:28:36 by ljerk             #+#    #+#             */
/*   Updated: 2020/09/28 21:47:55 by ljerk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

static void		push(int *tail, t_room **a, t_room *x)
{
	a[*tail] = x;
	*tail += 1;
}

static t_room	*pop(int *head, int *tail, t_room **room)
{
	if (*head != *tail)
	{
		*head += 1;
		return (room[*head - 1]);
	}
	else
		ft_printf("Error\n");
	return (0);
}

static void		init_bfs(t_lemin *lem, int *head, int *tail)
{
	int	i;

	i = 0;
	*head = 0;
	*tail = 0;
	while (i < lem->num_rooms)
	{
		lem->rooms[i].depth = -1;
		lem->rooms[i].visited = 0;
		i++;
	}
	lem->start_room->depth = 0;
	lem->start_room->visited = 1;
	lem->end_room->depth = 2147483647;
}

static	void	ft_help(t_room *node, t_room **queue, int *tail, int i)
{
	if (node->n_rooms[i]->visited == 0 && node->blocks[i] == 0)
	{
		push(tail, queue, node->n_rooms[i]);
		node->n_rooms[i]->visited = 1;
		node->n_rooms[i]->depth = node->depth + 1;
	}
}

int				bfs(t_lemin *lem)
{
	t_room	**queue;
	t_room	*node;
	int		tail;
	int		head;
	int		i;

	tail = 0;
	head = 0;
	if ((queue = (t_room**)ft_memalloc(sizeof(t_room*)\
			* lem->num_rooms)) == NULL)
		exit(1);
	init_bfs(lem, &tail, &head);
	push(&tail, queue, lem->start_room);
	while (!(head == tail))
	{
		node = pop(&head, &tail, queue);
		i = -1;
		while (++i < node->num_links)
			ft_help(node, queue, &tail, i);
	}
	free(queue);
	return (0);
}
