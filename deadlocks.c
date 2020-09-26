/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deadlocks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerk <ljerk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 09:28:36 by ljerk             #+#    #+#             */
/*   Updated: 2020/09/26 22:07:56 by ljerk            ###   ########.fr       */
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
/* 
	stack - стек комнат для обработки bfs
	room_id - индекс комнаты, которую обрабатывается сейчас(соседи которой добавляем в стек)
	ins_place - место в стеке, куда должна встать следубщая комната

int		add_to_stack(t_room **stack, int room_id, int ins_place)
{
	int	i;

	i = 0;
	while (i < stack[room_id]->n_rooms[i]->num_links)
	{
		stack[ins_place] = stack[room_id]->n_rooms[i];
		if (stack[ins_place]->name == stack[0]->name || stack[1].)
			return (0);
		i++;
		ins_place++;
	}
}

t_room **shortest_path(t_lemin *lem)
{
	t_room	**shortest_path;//стек с кратчайшим путем от start до end
	int	i;		//номер рассматриваемой комнаты
	int	j;		//номер комнаты в shortest_path
	int	insert_place;	//место в стеке комнат куда встанет следующая комната
	t_room	**stk;		//стек комнат
	
	init_shortest_path(lem, stk);//добавляем в стек связи с end`ом
	while(add_to_stack(stk, i, insert_place))//1 - не дошли до старта, 0 - дошли
	{
		shortest_path[j] = min_depth(stk);
		j++;
	}
}*/

/* static t_room **init_bfs(t_lemin *lem, t_room **stk)
{
	lem->start_room->depth = 0;
	stk[0] = lem->start_room;
	stk[0]->visited = 1;
	lem->end_room->depth = 2147483647;
	stk[lem->num_rooms - 1] = lem->end_room;
	stk[lem->num_rooms - 1]->visited = 1;
	return (stk);
} */


    //Для более лаконичной реализации работы, мы будем
    //хранить указатель не на последний элемент, а
    //на следующий за ним (несуществующий).

    //Это, в частности, позволит нам проверять очередь на пустоту
    //простым условием head == tail
    //int head = 0;    Индекс первого элемента.
    //int tail = 0;    Индекс элемента, следующего за последним.

void push(int *tail, t_room **a, t_room *x)
{
	a[*tail] = x;
	*tail += 1;
}

t_room	*pop(int *head, int *tail, t_room **a) {
	if (*head != *tail)
	{
		*head += 1;
		return a[*head - 1];
	}
	else
		return (0);// СДЕЛАТЬ ОБРАБОТКУ Ошибка, попытка извлечь элемент из пустой очереди.
}

int is_empty(int head, int tail)
{
	return head == tail;
}

//алгоритм расставляет глубины комнат
/* t_room	**bfs(t_lemin *lem)
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
	i = -1;
	while (++i < lem->num_rooms)
	{
		j = -1;
		while (++j < stk[i]->num_links)
			if (stk[i]->n_rooms[j]->visited == 0)
			{
				stk[insert_place] = stk[i]->n_rooms[j];
				stk[insert_place]->visited = 1;
				stk[insert_place]->depth = stk[i]->depth + 1;
				insert_place++;
			}
	}
	
	while (all_visited(stk) != 0)
	{
		
	}
	return (stk);
} */

void		find_pathes(t_lemin *lem)
{
	int max_pathes;
	t_room **room_arr;

	max_pathes = lem->start_room->num_links < lem->end_room->num_links ? \
		lem->start_room->num_links : lem->end_room->num_links;

	/********Для тестирования*********/
	int head = 0;
	int tail = 0;	
	if ((room_arr = (t_room**)ft_memalloc(sizeof(t_room*) * lem->num_rooms)) == NULL)
		exit(1);
	push(&tail, room_arr, lem->end_room);
	ft_printf("%s\n", room_arr[0]->name);
	ft_printf("%d\n%d\n%d", is_empty(head, tail), head, tail);
	/********Для тестирования*********/
	
	//room_arr = bfs(lem);
	/* 
	поправить bfs чтобы граф ex2_1.map считал вершины так: 0 1 2 4 3
	сделать, чтобы bfs работал до тех пор, пока не дойдет до узла end 
		или пока не кончатся комнаты или пока не кончатся комнаты в очереди
	*/
	/* int i = 0;
	while (i < lem->num_rooms)
	{
		ft_printf("%s ", room_arr[i]->name);
		i++;
	} */
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