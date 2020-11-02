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

void	del_first_link(int id_isol_room, t_lemin *lem)
{
	int	i;

	i = 0;
	while (i < lem->start_room->num_links)
	{
		if (id_isol_room == lem->start_room->n_rooms[i]->id)
			lem->start_room->blocks[i] = 1;
		i++;
	}
}

void	restore_first_link(int id_restore_room, t_lemin *lem)
{
	int	i;

	i = 0;
	while (i < lem->start_room->num_links)
	{
		if (id_restore_room == lem->start_room->n_rooms[i]->id)
			lem->start_room->blocks[i] = 0;
		i++;
	}
}

int		isolated(t_room *room)
{
	int i;

	i = 0;
	while (i < room->num_links)
	{
		if (room->blocks[i] == 0)
			return (0);//комната НЕ изолирована
		i++;
	}
	return (1);//комната изолирована
}

void	move_back(t_lemin *lem, t_path *path)
{
	t_room	*room;//рассматриваемая комната
	t_room	**sh; //shortest path
	int		i;
	int		ins;

	ins = lem->end_room->depth;
	room = lem->end_room;
	//кратчайший путь имеет длину = глубине конечной комнаты
	if ((sh = (t_room**)ft_memalloc(sizeof(t_room*) * \
			(lem->end_room->depth + 1))) == NULL)
		exit(1);
	while (room->id != lem->start_room->id)//while rooms aren`t equal
	{
		i = 0;
		while (room->n_rooms[i]->depth != room->depth - 1 && i < room->num_links)
			i++;
		sh[ins] = room;
		ins--;
		room = room->n_rooms[i];
	}
	sh[ins] = room;//была стартовая
	path->sh = sh;
	path->length = lem->end_room->depth + 1;
	/* int j = 0;
	while (j <= ins)
		free(sh[j++]); */
	//free(sh);
}

int			check_shortcut(t_lemin *lem)
{
	int	i;

	i = 0;
	while (i < lem->start_room->num_links)
	{
		if (lem->start_room->n_rooms[i]->id == lem->end_room->id)
			return (1);
		i++;
	}
	return (0);
}
//удалить
//выводит из каких name состоит путь
void		print_path(t_path *path)
{
	int i;

	i = 0;
	ft_printf("name chain ");
	while (i < path->length)
	{
		if (i != path->length - 1)
			ft_printf("%s-", path->sh[i]->name);
		else
			ft_printf("%s\n\n", path->sh[i]->name);
		i++;
	}
}

void		print_path_color(t_path *path)
{
	int i;

	i = 0;
	ft_printf(CYN"\n\nname chain\n"RST);
	while (i < path->length)
	{
		if (i != path->length - 1 && i % 2 == 0 && i % 4 != 0 && i % 6 != 0)
			ft_printf(RED"%s->"RST, path->sh[i]->name);
		else if (i != path->length - 1 && i % 3 == 0 && i % 6 != 0)
			ft_printf(GRN"%s->"RST, path->sh[i]->name);
		else if (i != path->length - 1 && i % 4 == 0)
			ft_printf(YEL"%s->"RST, path->sh[i]->name);
		else if (i != path->length - 1 && i % 5 == 0)
			ft_printf(BLU"%s->"RST, path->sh[i]->name);
		else if (i != path->length - 1 && i % 6 == 0)
			ft_printf(MAG"%s->"RST, path->sh[i]->name);
		else if (i != path->length - 1 && i % 7 == 0)
			ft_printf(CYN"%s->"RST, path->sh[i]->name);
		else if (i != path->length - 1)
			ft_printf(CYN"%s->"RST, path->sh[i]->name);
		else if (i == path->length - 1)
			ft_printf("%s\n", path->sh[i]->name);
		i++;
	}
}

//удалить
void		print_depth(t_lemin lem)
{
	int	i = 0;

	while (i < lem.num_rooms)
	{
		ft_printf("name: %s depth: %d\n",lem.rooms[i].name, lem.rooms[i].depth);
		i++;
	}
}


void		init_id(t_lemin *lem)
{
	int	id;

	id = 0;
	while (id < lem->num_rooms)
	{
		lem->rooms[id].id = id;
		id++;
	}
}

int		solver(t_path **mas, t_lemin *lem, t_path *path1, t_path *path2)
{
	bfs(lem);
	if (lem->end_room->depth == 2147483647)
		return (1);
	move_back(lem, path1);
	lem->max_pathes--;
	if (lem->max_pathes > 0)
	{
		del_first_link(path1->sh[1]->id, lem);
		bfs(lem);
		if (lem->end_room->depth == 2147483647)
			return (1);
		move_back(lem, path2);
		restore_first_link(path1->sh[1]->id, lem);
		path_type(mas, lem, path1, path2);
	}
	else
	{
		mas[lem->ins] = path1;
        lem->ins++;
		del_path(path1);
		//free_path(path1);
	}
	return (0);
}

t_path		**find_pathes(t_lemin *lem)
{
	t_path	*path1;
	t_path	*path2;
	t_path	**mass_pathes;

	lem->ins = 0;
	init_id(lem);//можно перенести в main.c
	if (check_shortcut(lem) == 1)
	{
		ft_printf("start-end link founded");
		exit(0);//движение сразу всех муравьев
	}
	lem->max_pathes = lem->start_room->num_links < lem->end_room->num_links ? \
		lem->start_room->num_links : lem->end_room->num_links;
	if ((mass_pathes = (t_path**)ft_memalloc(sizeof(t_path*) * lem->max_pathes)) == NULL)
		exit(1);
	while (lem->max_pathes > 0 && !isolated(lem->start_room))
	{
		if (((path1 = (t_path*)ft_memalloc(sizeof(t_path))) == NULL) || \
			((path2 = (t_path*)ft_memalloc(sizeof(t_path))) == NULL))
			exit(1);
		if (solver(mass_pathes, lem, path1, path2) == 1)
			break ;
		/* free(path1);
		free(path2); */
	}
	return (mass_pathes);
}
//добавить как бонус вывод путей