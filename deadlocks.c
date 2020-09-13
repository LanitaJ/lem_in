/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deadlocks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerk <ljerk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 09:28:36 by ljerk             #+#    #+#             */
/*   Updated: 2020/09/13 14:33:26 by ljerk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

/* void		find_path(t_lemin *lem)
{
	t_room *path;

	if ((path = (t_room*)ft_memalloc(sizeof(t_room) * lem->num_rooms)) == NULL)
		exit(1);
	
} */

//создание начальных значений в стеке комнат
static t_room **init_bfs(t_lemin *lem, t_room **room_arr)
{
	lem->start_room->depth = 0;
	room_arr[0] = lem->start_room;
	room_arr[0]->in_stack = 1;
	lem->end_room->depth = 2147483647;
	room_arr[lem->num_rooms - 1] = lem->end_room;
	room_arr[lem->num_rooms - 1]->in_stack = 1;
	return(room_arr);
}

//алгоритм расставляет глубины комнат
t_room	**bfs(t_lemin *lem)
{
	t_room	**stk;			//стек комнат
	int		insert_place;	//место в стеке комнат куда встанет следующая комната
	int		i;				//номер рассматриваемой комнаты
	int		j;				//счетчик для заполнения стека

	i = -1;
	insert_place = 1;
	if ((stk = (t_room**)ft_memalloc(sizeof(t_room*) * lem->num_rooms)) == NULL)
		exit(1);
	init_bfs(lem, stk);
	while (++i < lem->num_rooms)
	{
		j = -1;
		while (++j < stk[i]->num_links)
			if (stk[i]->n_rooms[j]->in_stack == 0)
			{
				stk[insert_place] = stk[i]->n_rooms[j];
				stk[insert_place]->in_stack = 1;
				stk[insert_place]->depth = stk[i]->depth + 1;
				insert_place++;
			}
	}
	return (stk);
}

void		find_pathes(t_lemin *lem)
{
	int max_pathes;
	t_room **room_arr;

	max_pathes = lem->start_room->num_links < lem->end_room->num_links ? \
		lem->start_room->num_links : lem->end_room->num_links;
	room_arr = bfs(lem);
	int i = 0;
	while (i < lem->num_rooms)
	{
		ft_printf("%d ", room_arr[i]->depth);
		i++;
	}
}



/* 



BFS(start_node, goal_node)
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
}

(1)BFS расставляет глубину для каждого узла
(2)После BFS идем с конца в начало и ищем кратчайший путь и запоминаем его
(3)записываем путь в массив
(4)разворачиваем ребра
   goto (1)
*/