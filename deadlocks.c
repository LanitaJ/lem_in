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

void	del_first_link(char *isol_room, t_lemin *lem)
{
	int	i;

	i = 0;
	while (i < lem->start_room->num_links)
	{
		//ft_printf("%d %s %s\n", i, lem->start_room->n_rooms[i]->name, isol_room);
		if (ft_strequ(lem->start_room->n_rooms[i]->name, isol_room) == 1)
		{
			lem->start_room->blocks[i] = 1;
			//lem->start_room->n_rooms[i]->blocks
			//как заблокировать старт? и нужно ли?
		}
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

void print_queue(t_room **queue, t_lemin *lem)
{
	int i;

	i = 0;
	while (i < lem->num_rooms)
	{
		if (queue[i] != NULL)
			ft_printf("%s ",queue[i]->name);
		i++;
	}
	ft_printf("\n");
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
	if ((sh = (t_room**)ft_memalloc(sizeof(t_room*) * (lem->end_room->depth + 1))) == NULL)
		exit(1);
	while (ft_strequ(room->name, lem->start_room->name) == 0)//1 = rooms are equal
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
}

int			check_shortcut(t_lemin *lem)
{
	int	i;

	i = 0;
	while (i < lem->start_room->num_links)
	{
		if (ft_strequ(lem->start_room->n_rooms[i]->name, lem->end_room->name) == 1)
			return (1);
		i++;
	}
	return (0);
}
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

void		print_depth(t_lemin lem)
{
	int	i = 0;

	while (i < lem.num_rooms)
	{
		ft_printf("name: %s depth: %d\n",lem.rooms[i].name, lem.rooms[i].depth);
		i++;
	}
}
void		del_path(t_path *path)
{
	int	i;
	int	j;
	
	i = 0;
	//ft_printf("dep %d\n", path->length);
	while (i < path->length)
	{
		j = -1;
		while (j++ < path->sh[i]->num_links)
			path->sh[i]->blocks[j] = 1;
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
		//ft_printf("name %s | id %d\n",lem->rooms[id].name, id);
		id++;
	}
}

void		find_pathes(t_lemin *lem)
{
	int		max_pathes;
	char	*first_link;
	t_path	*path1;
	t_path	*path2;
	int		type;

	if (check_shortcut(lem) == 1)
	{
		ft_printf("start-end link founded");
		exit(0);//движение сразу всех муравьев 
	}
	max_pathes = lem->start_room->num_links < lem->end_room->num_links ? \
		lem->start_room->num_links : lem->end_room->num_links;
	/* if (max_pathes == 1)
	{
		добавить обработку, когда возможен только один кратчайший путь
	} */
	//уменьшать max_pathes при сохранении путей
	/* while (max_pathes > 0 && !isolated(lem.start_room))
	{

	} */
	//можно объединить функции
	if (((path1 = (t_path*)ft_memalloc(sizeof(t_path))) == NULL) || \
		((path2 = (t_path*)ft_memalloc(sizeof(t_path))) == NULL))
		exit(1);
	init_id(lem);
	//output_map(*lem);
	bfs(lem);
	//print_depth(lem);
	move_back(lem, path1);
	print_path(path1);
	
	first_link = path1->sh[1]->name;
	del_first_link(first_link, lem);
	//можно поменять на id комнаты
	//ft_printf("\n\ndeleted%s", first_link);

	bfs(lem);
	//print_depth(lem);
	move_back(lem, path2);
	print_path(path2);

	//del_path(path1);
	//del_path(path2);
	type = choose_type(lem, path1, path2);
	ft_printf("type %d", type);
	/*if (type == 1)
	{
		del_path(sh2);
	} */
	//output_map(*lem);
	

	
	
}

/* BFS(start_node, goal_node)
{	
	for(all nodes i)
		visited[i] = false; // изначально список посещённых узлов пуст
	
	queue.push(start_node);              // начиная с узла-источника
	visited[start_node] = true;
	while(! queue.empty() )					 // пока очередь не пуста
	{           
		node = queue.pop();                 // извлечь первый элемент в очереди
		if(node == goal_node)
			return true;                       // проверить, не является ли текущий узел целевым
  		foreach(child in expand(node))    // все преемники текущего узла, ...
		{
			if(visited[child] == false)       // ... которые ещё не были посещены ...
			{
				queue.push(child);                // ... добавить в конец очереди...
    			visited[child] = true;            // ... и пометить как посещённые
   			}
  		}
 	}
	return false;                        // Целевой узел недостижим
} */
