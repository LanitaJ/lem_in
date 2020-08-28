#include "lemin.h"
#include <stdio.h>

typedef struct	s_link
{
	char* p1;
	char* p2;
}				t_link;

typedef struct	s_room
{
	char* name;
	int x;
	int y;
}				t_room;

typedef	struct	s_lemin
{
	int 		num_links;
	int			num_ants;
	int			num_rooms;
	t_room*		rooms;
	t_room		start_room;
	t_room		end_room;
	t_link*		links;
}				t_lemin;

int numlen(int nbr)
{
	int i = 0;
	while(nbr /= 10)
		i++;
	return i + 1;
}

int get_room(char* line, t_room *room)
{
	int i;

	i = 0;
	while(line[i] != '\0')
	{
		if(line[i] == ' ')
		{
			room->name = ft_strnew(i);
			ft_strncpy(room->name, line, i);
			line += i + 1;
			room->x = ft_atoi(line);
			line += numlen(room->x);
			room->y = ft_atoi(line);
			return 1;
		}
		i++;
	}
	return 0;
}

int add_room(t_lemin *lem, char* line)
{
	t_room* tmp;
	int i = -1;

	tmp = (t_room*)malloc(sizeof(t_room) * ++(lem->num_rooms));
	while(++i != lem->num_rooms - 1)
		tmp[i] = lem->rooms[i];
	get_room(line, &tmp[i]);
	free(lem->rooms);
	free(line);
	lem->rooms = tmp;
	return 1;
}

int get_rooms(t_lemin *lem)
{
	char* line;

	while(get_next_line(0, &line) && ft_strcmp(line, "# links"))
	{
		if (!ft_strcmp(line, "##start"))
		{
			free(line);
			get_next_line(0, &line);
			get_room(line, &lem->start_room);
		}
		else if (!ft_strcmp(line, "##end"))
		{
			free(line);
			get_next_line(0, &line);
			get_room(line, &lem->end_room);
		}
		else
			add_room(lem, line);
	}
	return 1;
}

int compare(t_lemin *lem,char* str)//return number of equivalent char* with rooms
{
	int i;
	int equil;

	i = 0;
	equil = 0;
	while(i != lem->num_rooms)
	{
		if(!strcmp(lem->rooms[i].name, str))
			equil++;
		i++;
	}
	equil += (!strcmp(lem->start_room.name, str)) + (!strcmp(lem->end_room.name, str));
	if (!equil)
		exit(1);
	return (equil);
}

int get_link(char* line, t_link *l, t_lemin *lem)//переделать
{
	int i;

	i = 0;
	while(i != strlen(line))
	{
		l->p1 = ft_strnew(i);
		ft_strncpy(l->p1, line, i);
		if (line[i] == '-')
		{
			if (compare(lem, l->p1) == 1)
			{
				line += i + 1;
				i = 0;
				while(i != strlen(line))
				{
					l->p2 = ft_strnew(strlen(line));
					ft_strcpy(l->p2, line);
					if (compare(lem, l->p2) == 1)
						return 1;
					i++;
				}
				return 0;
			}
		}
		i++;
	}
	return 0;
}

int add_link(t_lemin *lem, char* line)
{
	t_link* tmp;
	int i = -1;

	tmp = (t_link*)malloc(sizeof(t_link) * ++(lem->num_links));
	while(++i != lem->num_links - 1)
		tmp[i] = lem->links[i];
	get_link(line, &tmp[i], lem);
	if (lem->num_links != 1)
		free(lem->links);
	free(line);
	lem->links = tmp;
	return 1;
}

int get_links(t_lemin *lem)
{
	char* line;
	int i;

	i = 0;
	while(get_next_line(0, &line))
		add_link(lem, line);
	return 1;
}

int parse(t_lemin *lem)
{
	char* line;

	get_next_line(0, &line);
	lem->num_ants = ft_atoi(line);
	free(line);
	get_rooms(lem);
	get_links(lem);
	return 1;
}

void init_lemin(t_lemin *lem)
{
	lem->num_rooms = 0;
	lem->num_links = 0;
}

int main()
{
	t_lemin lem;

	init_lemin(&lem);
	parse(&lem);
	int i = 0;
	while(i != lem.num_rooms)
	{
		ft_putstr(lem.rooms[i].name);
		ft_putchar(' ');
		ft_putnbr(lem.rooms[i].x);
		ft_putchar(' ');
		ft_putnbr(lem.rooms[i].y);
		ft_putchar(' ');
		ft_putchar('\n');
		i++;
	}
	ft_putstr(lem.start_room.name);
	ft_putchar(' ');
	ft_putnbr(lem.start_room.x);
	ft_putchar(' ');
	ft_putnbr(lem.start_room.y);
	ft_putchar(' ');
	ft_putchar('\n');
	ft_putstr(lem.end_room.name);
	ft_putchar(' ');
	ft_putnbr(lem.end_room.x);
	ft_putchar(' ');
	ft_putnbr(lem.end_room.y);
	ft_putchar(' ');
	ft_putchar('\n');

 	int j = 0;
 	while(j != lem.num_links)
	{
 		ft_putstr(lem.links[j].p1);
 		ft_putstr("-");
		ft_putstr(lem.links[j].p2);
		ft_putchar('\n');
		j++;
	}
	return 0;
}
