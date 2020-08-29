#include "lemin.h"
#include <stdio.h>



typedef struct	s_link
{
	char* p1;
	char* p2;
}				t_link;

typedef struct	s_room
{
	char*		name;
	int			x;
	int			y;
	struct t_rlink*	links;
	int			num_links;
}				t_room;

typedef struct	s_rlink
{
	t_room*		room;
	int			block;
	t_rlink		*next;
}				t_rlink;

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

//чек на имя комнаты

int check_room(char* line)
{
	int i;
	int space;

	i = 0;
	space = 0;
	while(line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			if (line[i + 1] != ' ')
				space++;
		}
		else if (!ft_isdigit(line[i]))
			return 0;
		i++;
	}
	return (space == 2) ? 1 : 0;
}

int check_line(char* line)
{
	if (line[0] == '#') {
		return 1;
	}
	return check_room(line);
}

void exit_get_room(char* line)
{
	if (!check_room(line))
	{
		ft_putstr("get_room");
		exit(1);
	}
}

char *get_rooms(t_lemin *lem, char* line)
{
	while(get_next_line(0, &line) && check_line(line))
	{
		if (!ft_strcmp(line, "##start"))
		{
			get_next_line(0, &line);
			exit_get_room(line);
			get_room(line, &lem->start_room);
			free(line);
		}
		else if (!ft_strcmp(line, "##end"))
		{
			get_next_line(0, &line);
			exit_get_room(line);
			get_room(line, &lem->end_room);
			free(line);
		}
		else if (line[0] == '#') {
			free(line);
		}
		else
			add_room(lem, line);
	}
	return line;
}

int compare(t_lemin *lem, char* str)//return number of equivalent char* with rooms
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
	if (equil != 1)
	{
		ft_putstr("compare ");
		ft_putstr(str);
		exit(1);
	}
	return (equil);
}

int get_first_room(char* line, t_link *l)
{
	int i;
	int len = 0;
	char *c;

	i = 0;
	while(line[i] != '\0')
	{
		if (line[i] == '-')
		{
			len = i;
			l->p1 = ft_strnew(i);
			i = 0;
			while (i != len)
			{
				l->p1[i] = line[i];
				i++;
			}
			return 1;
		}
		i++;
	}
	return 0;
}

int get_second_room(char *line, t_link *l)
{
	int		i;
	int		len;

	len = (int)(ft_strlen(line) - 1);
	l->p2 = ft_strnew(len);
	i = 0;
	while(i != len)
	{
		l->p2[i] = line[i + 1];
		i++;
	}
	return 1;
}

void get_link(char* line, t_link *l, t_lemin *lem)
{

	if(!get_first_room(line, l))
	{
		ft_putstr("get_link ");
		ft_putstr(line);
		exit(0);
	}
	if(!get_second_room(ft_strchr(line, '-'),l))
	{
		ft_putstr("get_link ");
		ft_putstr(line);
		exit(0);
	}
	if (!(compare(lem,l->p1) * compare(lem,l->p2)))
	{
		ft_putstr("compare ");
		ft_putstr(line);
		exit(0);
	}
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

int get_links(t_lemin *lem, char *line)
{
	int i;

	i = 0;
	add_link(lem, line);
	while(get_next_line(0, &line))
		add_link(lem, line);
	return 1;
}

int create_trlink(t_room *room)
{
	t_rlink *new;

	new = (t_rlink *)malloc(sizeof(t_rlink));
	new->next = (void*)0;
	new->room = room;
	return 0;
}

int add_trlink(t_room *room, t_rlink *prev)
{
	t_rlink *new;

	new = (t_rlink *)malloc(sizeof(t_rlink));
	new->next = (void*)0;
	new->room = room;
	prev->next = new;
	return 0;
}

t_rlink *last_trlink(t_rlink *rlink)
{
	while (rlink->next)
		rlink = rlink.next;
	return rlink;
}

int altor(t_lemin *lem)//add links to rooms
{
	int i;
	int j;

	i = 0;
	while(i != lem->num_rooms - 1)
	{
		lem->rooms[i].num_links = 0;
		j = 0;
		while(j != lem->num_links - 1)
		{
			if((!ft_strcmp(lem->rooms[i].name, lem->links[j].p1)) || (!ft_strcmp(lem->rooms[i].name, lem->links[j].p2)))
			{
				lem->rooms[i].num_links++;
				if (lem->rooms[i].num_links == 1)
					create_trlink(lem->rooms[i]);
				else
					add_trlink(lem->rooms[i], last_trlink(lem->rooms[i].links[0]));
			}
			j++;
		}
		i++;
	}
}

int parse(t_lemin *lem)
{
	char* line;

	get_next_line(0, &line);
	lem->num_ants = ft_atoi(line);
	free(line);
	get_links(lem,get_rooms(lem,line));
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

 	altor(lem);

	return 0;
}
