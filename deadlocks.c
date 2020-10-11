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




    //Для более лаконичной реализации работы, мы будем
    //хранить указатель не на последний элемент, а
    //на следующий за ним (несуществующий).

    //Это, в частности, позволит нам проверять очередь на пустоту
    //простым условием head == tail
    //int head = 0;    Индекс первого элемента.
    //int tail = 0;    Индекс элемента, следующего за последним.

int		isolated(t_room *room)
{
	if (room->num_links == 0)
		return (1);
	return (0);
}

void	push(int *tail, t_room **a, t_room *x)
{
	a[*tail] = x;
	*tail += 1;
}

t_room	*pop(int *head, int *tail, t_room **room) {
	if (*head != *tail)
	{
		*head += 1;
		return (room[*head - 1]);
	}
	else
		ft_printf("Error\n");// СДЕЛАТЬ ОБРАБОТКУ Ошибка, попытка извлечь элемент из пустой очереди.
	return(0);//убрать
}

int is_empty(int head, int tail)
{
	return (head == tail);
}

static	void init_bfs(t_lemin *lem, int *head, int *tail)
{
	int	i;

	i = 0;
	*head = 0;
	*tail = 0;
	while (i < lem->num_rooms)
		lem->rooms[i++].depth = -1;
	lem->start_room->depth = 0;
	lem->start_room->visited = 1;
	lem->end_room->depth = 2147483647;
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

t_room	**move_back(t_lemin *lem)
{
	t_room	*room;
	t_room	**sh; //shortest path
	int		i;
	int		ins;

	ins = lem->end_room->depth;
	room = lem->end_room;
	//кратчайший путь имеет длину = глубине конечной комнаты
	if ((sh = (t_room**)ft_memalloc(sizeof(t_room*) * (lem->end_room->depth + 1))) == NULL)
		exit(1);
	//sh[lem->end_room->depth] = lem->end_room;
	while (ft_strequ(room->name, lem->start_room->name) == 0)//1 = rooms are equal
	{
		i = 0;
		while (room->n_rooms[i]->depth != room->depth - 1 && i < room->num_links)
			i++;
		sh[ins] = room;
		ins--;
		room = room->n_rooms[i];
	}
	sh[ins] = lem->start_room;
	return(sh);
}

//алгоритм расставляет глубины комнат
int		bfs(t_lemin *lem)
{
	t_room	**queue;			//очередь комнат
	t_room	*node;
	int		tail = 0;
	int		head = 0;
	int		i;
	
	if ((queue = (t_room**)ft_memalloc(sizeof(t_room*) * lem->num_rooms)) == NULL)
		exit(1);
	init_bfs(lem, &tail, &head);
	push(&tail, queue, lem->start_room);
	while (!is_empty(head, tail))
	{
		//int k = 0;
		node = pop(&head, &tail, queue);
		/* ft_printf("current node %s\nlinks: ", node->name);
		while (k < node->num_links)
		{
			ft_printf("%s ", node->n_rooms[k]->name);
			k++;
		}
		ft_printf("\n");
		if (ft_strequ(node->name, lem->end_room->name))
		{
			ft_printf("end\n");
			return (1);
		} */	
		i = -1;
		while (++i < node->num_links)
			if (node->n_rooms[i]->visited == 0)
			{
				//ft_printf("name = %s\n", node->n_rooms[i]->name);
				//ft_printf("numlink %d\n", node->num_links);
				push(&tail, queue, node->n_rooms[i]);
				node->n_rooms[i]->visited = 1;
				node->n_rooms[i]->depth = node->depth + 1;
			}
	}
	return (0);
}


void		find_pathes(t_lemin *lem)
{
	int max_pathes;
	int i = 0;
	t_room	**sh;

	max_pathes = lem->start_room->num_links < lem->end_room->num_links ? \
		lem->start_room->num_links : lem->end_room->num_links;
	bfs(lem);
	while (i < lem->num_rooms)
	{
		ft_printf("name: %s depth: %d\n",lem->rooms[i].name, lem->rooms[i].depth);
		i++;
	}
	i = 0;
	sh = move_back(lem);
	while (i <= lem->end_room->depth)
	{
		ft_printf("%s-", sh[i]->name);
		i++;
	}
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
