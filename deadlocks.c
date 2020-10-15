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

t_room	**move_back(t_lemin *lem)
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
	sh[ins] = lem->start_room;
	return(sh);
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

void		print_path(t_lemin lem, t_room **sh)
{
	int i;

	i = 0;
	while (i <= lem.end_room->depth)
	{
		if (i != lem.end_room->depth)
			ft_printf("%s-", sh[i]->name);
		else
			ft_printf("%s\n\n", sh[i]->name);
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

void		find_pathes(t_lemin lem)
{
	int		max_pathes;
	char	*first_link;
	t_room	**sh1;
	t_room	**sh2;

	if (check_shortcut(&lem) == 1)
	{
		ft_printf("start-end link founded");
		exit(0);//движение сразу всех муравьев 
	}
	max_pathes = lem.start_room->num_links < lem.end_room->num_links ? \
		lem.start_room->num_links : lem.end_room->num_links;
	//уменьшать max_pathes при сохранении путей
	/* while (max_pathes > 0 && !isolated(lem.start_room))
	{

	} */
	//можно объединить функции
	bfs(&lem);	
	print_depth(lem);
	sh1 = move_back(&lem);	
	print_path(lem, sh1);
	first_link = sh1[1]->name;
	//ft_printf("\n\ndeleted%s", first_link);
	del_first_link(first_link, &lem);
	
	bfs(&lem);
	print_depth(lem);
	sh2 = move_back(&lem);
	print_path(lem, sh2);
	
	
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
