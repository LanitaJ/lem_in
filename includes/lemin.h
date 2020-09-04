/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerk <ljerk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:11:57 by ljerk             #+#    #+#             */
/*   Updated: 2020/09/04 19:37:30 by ljerk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../ft_printf/includes/ft_printf.h"


typedef struct	s_link
{
	char* name1;
	char* name2;
}				t_link;

typedef struct	s_room
{
	char*		name;
	int			x;
	int			y;
	struct s_room*		*n_rooms;
	int			*blocks;
	int			num_links;
}				t_room;

typedef	struct	s_lemin
{
	int 		num_links;
	int			num_ants;
	int			num_rooms;
	int			fd;
	t_room*		rooms;
	t_room		start_room;
	t_room		end_room;
	t_link*		links;
}				t_lemin;



void	get_link(char* line, t_link *l, t_lemin *lem);
int		add_link(t_lemin *lem, char* line);
int		parse_links(t_lemin *lem);
int		create_link(t_room *main_room, t_link *link, t_lemin *lem);
int		check_link(char *line);
int		get_links(t_lemin *lem, char *line);
char	*get_rooms(t_lemin *lem, char* line);
int		get_room(char* line, t_room *room);
int		add_room(t_lemin *lem, char* line);
void	exit_get_room(char* line);
int		get_first_room(char* line, t_link *l);
int		get_second_room(char *line, t_link *l);

int		numlen(int nbr);
int		check_room(char* line);
int		check_line(char* line);
int		compare(t_lemin *lem, char* str);//return number of equivalent char* with rooms
t_room	*name_to_room(char *name, t_lemin *lem);
int		add_room_to_room(t_room *main_room, char* name_add, t_lemin* lem);
int		altor(t_lemin *lem);


void	error_ant_count(char *line);
void	error_trash(char *line);
void	error_memmory(char *line);
void	error_map(char *line);
void	error_link(char *line);


