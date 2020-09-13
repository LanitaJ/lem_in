/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deadlocks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerk <ljerk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 09:28:36 by ljerk             #+#    #+#             */
/*   Updated: 2020/09/13 13:37:25 by ljerk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

//void fill_pathes(t_lemin *lem)для тестирования
//{
	//ft_bzero(lem, sizeof(t_lemin*));
	/* lem = ft_memalloc(sizeof(t_lemin*));
	lem->num_ants = 20;
	lem->start_room.n_rooms = (t_room**)malloc(sizeof(t_room) * 2);
	lem->rooms = (t_room*)malloc(sizeof(t_room) * 2);
	 */
	

	/* 
	lem->start_room.n_rooms[0] = &lem->rooms[1];
	lem->start_room.n_rooms[0]->name = lem->rooms[1].name;
	lem->rooms[0].n_rooms[1] = &lem->rooms[2];
	lem->start_room.n_rooms[1]->name = lem->rooms[2].name;
	lem->start_room.num_links = 2;
	
	lem->rooms[0].name = "1";
	lem->rooms[0].n_rooms[0] = &lem->end_room;
	lem->rooms[0].n_rooms[0]->name = lem->end_room.name;
	lem->start_room.num_links = 1;


	lem->rooms[1].name = "2";
	lem->rooms[1].n_rooms[0] = &lem->rooms[2];
	lem->rooms[1].n_rooms[0]->name = lem->rooms[2].name;
	lem->start_room.num_links = 1;

	lem->rooms[2].name = "3";
	lem->rooms[2].n_rooms[0] = &lem->end_room;
	lem->rooms[2].n_rooms[0]->name = lem->end_room.name;
	lem->start_room.num_links = 1; */
//}


/* void		find_path(t_lemin *lem)
{
	t_room *path;

	if ((path = (t_room*)ft_memalloc(sizeof(t_room) * lem->num_rooms)) == NULL)
		exit(1);
	
} */

void		bfs(t_lemin *lem)
{
	t_room	**room_arr;//стек комнат
	int		insert_place;//место в стеке комнат куда встанет следующая комната
	int		i;//номер рассматриваемой комнаты
	int		j;//счетчик для заполнения стека
	
	i = 0;
	insert_place = 1;
	if ((room_arr = (t_room**)ft_memalloc(sizeof(t_room*) * lem->num_rooms)) == NULL)
		exit(1);
	lem->start_room->depth = 0;
	room_arr[0] = lem->start_room;
	room_arr[0]->in_stack = 1;
	lem->end_room->depth = 2147483647;
	room_arr[lem->num_rooms - 1] = lem->end_room;
	room_arr[lem->num_rooms - 1]->in_stack = 1;
	//ft_printf("name %s\n", room_arr[lem->num_rooms-1]->name);
	int k;
	ft_printf("\nnum rooms %d\n", lem->num_rooms);
	while (i < lem->num_rooms)
	{
		ft_printf("name %s\n", room_arr[i]->name);
		k = 0;
		/* while (room_arr[k])
		{
			ft_printf("%s ", room_arr[k]->name);
			k++;
		} */
		room_arr[i]->visited = 1;
		j = 0;
		while (j < room_arr[i]->num_links)
		{
			if (room_arr[i]->n_rooms[j]->in_stack == 0)
			{
				room_arr[insert_place] = room_arr[i]->n_rooms[j];
				room_arr[insert_place]->in_stack = 1;
				room_arr[insert_place]->depth = room_arr[i]->depth + 1;
				insert_place++;	
			}
			j++;
		}
		i++;
		//ft_printf("i = %d\n", i++);
		//insert_place++;
	}
	
	i = 0;
	while (i < lem->num_rooms)
	{
		ft_printf("%d ", room_arr[i]->depth);
		i++;
	}
//что будет, если всего 2 комнаты?	
//	ft_printf("name %s\n", lem->end_room->name);
	
		
}

void		find_pathes(t_lemin *lem)
{
	int max_pathes;

	max_pathes = lem->start_room->num_links < lem->end_room->num_links ? \
		lem->start_room->num_links : lem->end_room->num_links;
	bfs(lem);
	/* ft_printf("%d\n", max_pathes);
	ft_printf("%d\n", lem->num_rooms);
	//fill_pathes(lem);
	ft_printf("%s\n", lem->rooms[0].n_rooms[0]->name);	
	ft_printf("%s\n", lem->start_room->name);
	ft_printf("%s\n", lem->end_room->name);
	ft_printf("%s\n", lem->rooms[3].name);
	ft_printf("%d\n", lem->rooms[3].blocks); */
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