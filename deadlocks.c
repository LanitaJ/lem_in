/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deadlocks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerk <ljerk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 09:28:36 by ljerk             #+#    #+#             */
/*   Updated: 2020/09/28 21:47:55 by ljerk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

t_room		**move_back(t_lemin *lem, t_path *path)
{
	t_room	*room;
	t_room	**sh;
	int		i;
	int		ins;

	ins = lem->end_room->depth;
	room = lem->end_room;
	if ((sh = (t_room**)malloc(sizeof(t_room*) * \
			(lem->end_room->depth + 1))) == NULL)
		exit(1);
	while (room->id != lem->start_room->id)
	{
		i = 0;
		while (room->n_rooms[i]->depth != room->depth - 1 &&\
									i < room->num_links)
			i++;
		sh[ins] = room;
		ins--;
		room = room->n_rooms[i];
	}
	sh[ins] = room;
	path->length = lem->end_room->depth + 1;
	return (sh);
}

int			find_sec_path(t_path *path1, t_path *path2,\
								t_lemin *lem, t_path **mas)
{
	del_first_link(path1->sh[1]->id, lem);
	bfs(lem);
	if (lem->end_room->depth == 2147483647)
	{
		free_path(path1);
		free(path2);
		return (1);
	}
	path2->sh = move_back(lem, path2);
	restore_first_link(path1->sh[1]->id, lem);
	path_type(mas, lem, path1, path2);
	return (0);
}

int			solver(t_path **mas, t_lemin *lem, t_path *path1, t_path *path2)
{
	bfs(lem);
	if (lem->end_room->depth == 2147483647)
	{
		free(path1);
		free(path2);
		return (1);
	}
	path1->sh = move_back(lem, path1);
	lem->max_pathes--;
	if (lem->max_pathes > 0)
		return (find_sec_path(path1, path2, lem, mas));
	else
	{
		mas[lem->ins] = path1;
		lem->ins++;
		del_path(path1);
		free(path2);
	}
	return (0);
}

t_path		**shortcut(t_lemin *lem, t_path **mass_pathes)
{
	t_path	*path;

	if ((path = (t_path*)ft_memalloc(sizeof(t_path))) == NULL)
		exit(1);
	if ((path->sh = (t_room**)ft_memalloc(sizeof(t_room*) * 2)) == NULL)
		exit(1);
	path->sh[0] = lem->start_room;
	path->sh[1] = lem->end_room;
	mass_pathes[0] = path;
	lem->ins++;
	lem->max_pathes--;
	return (mass_pathes);
}

t_path		**find_pathes(t_lemin *lem)
{
	t_path	*path1;
	t_path	*path2;
	t_path	**mass_pathes;

	lem->ins = 0;
	check_max_pathes(lem);
	if ((mass_pathes = (t_path**)malloc(sizeof(t_path*) \
		* lem->max_pathes)) == NULL)
		error_malloc();
	if (check_shortcut(lem) == 1)
		return (shortcut(lem, mass_pathes));
	while (lem->max_pathes > 0 && !isolated(lem->start_room))
	{
		if (((path1 = (t_path*)ft_memalloc(sizeof(t_path))) == NULL) || \
			((path2 = (t_path*)ft_memalloc(sizeof(t_path))) == NULL))
			error_malloc();
		if (solver(mass_pathes, lem, path1, path2) == 1)
			return (check_solution(lem, mass_pathes));
	}
	return (mass_pathes);
}
