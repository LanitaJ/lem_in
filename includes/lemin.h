/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:11:57 by ljerk             #+#    #+#             */
/*   Updated: 2020/11/10 15:21:06 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../ft_printf/includes/ft_printf.h"

# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define YEL	"\x1B[33m"
# define BLU	"\x1B[34m"
# define MAG	"\x1B[35m"
# define CYN	"\x1B[36m"
# define WHT	"\x1B[37m"
# define RST	"\x1B[0m"

typedef struct			s_link
{
	char*				name1;
	char*				name2;
}						t_link;

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	struct s_room		**n_rooms;
	int					*blocks;
	int					num_links;
	int					depth;
	int					visited;
	int					id;
}						t_room;

typedef struct			s_path
{
	t_room				**sh;
	int					length;
	int					count_ants;
}						t_path;

typedef	struct			s_ant
{
	int					nbr;
	t_room				*visited_room;
	t_path				*used_path;
}						t_ant;

typedef	struct			s_lemin
{
	int					num_links;
	int					num_ants;
	int					num_rooms;
	int					fd;
	int					id_start_room;
	int					id_end_room;
	int					check_start_kol;
	int					check_end_kol;
	int					max_pathes;
	int					stage;
	int					usable_aunts;
	int					ins;
	int					color;
	int					show_path;
	int					num_lines;
	t_room				*rooms;
	t_room				*start_room;
	t_room				*end_room;
	t_link				*links;
	t_ant				*ants;
}						t_lemin;

void					init_lemin(t_lemin *lem, int ac, char **av);
void					init_ants(t_lemin *lem);
void					init_lemin(t_lemin *lem, int ac, char **av);

void					get_link(char *line, t_link *l, t_lemin *lem);
int						add_link(t_lemin *lem, char *line);
void					parse_flags(char **av, t_lemin *lem);
int						create_link(t_room *main_room,\
							t_link *link, t_lemin *lem);
int						get_links(t_lemin *lem, char *line);
char					*get_rooms(t_lemin *lem, char *line);
int						get_room(char *line, t_room *room);
int						add_room(t_lemin *lem, char *line);
void					exit_get_room(char *line);
int						get_first_room(char *line, t_link *l);
int						get_second_room(char *line, t_link *l);
void					init_id(t_lemin *lem);

int						numlen(int nbr);
int						check_room(char *line);
int						check_line(char *line);
int						check_dblinks(t_lemin *lem);
int						compare(t_lemin *lem, char *str);
t_room					*name_to_room(char *name, t_lemin *lem);
int						add_room_to_room(t_room *main_room,\
							char *name_add, t_lemin *lem);
int						altor(t_lemin *lem);
void					count_aunts_for_pathes\
							(t_path	**mass_pathes, t_lemin *lem);
int						count_iterations(t_lemin *lem, t_path **mass_pathes);
void					count_aunts_for_pathes\
							(t_path **mass_pathes, t_lemin *lem);
t_room					*findnext(t_path *path, t_room *this_room);

void					error_ant_count(char *line);
void					error_link(char *line);
void					error_malloc();
void					error_count_args();
void					error_isolated_start(t_lemin *lem);
void					error_coord(t_lemin *lem, t_room *r1, t_room *r2);
void					error_start_end();
void					error_fd();
void					error_getrooms(char *line);

t_path					**find_pathes(t_lemin *lem);
int						bfs(t_lemin *lem);
void					print_path(t_path *path);
void					print_path_color(t_path *path);
void					print_solve(t_lemin *lem, t_path **mass_pathes);
void					path_type(t_path **mas, t_lemin *lem,\
							t_path *path1, t_path *path2);
void					del_path(t_path *path);
void					do_type1(t_lemin *lem, t_path **mas,\
							t_path *path1, t_path *path2);
void					do_type2_3(t_lemin *lem, t_path **mas,\
							t_path *path, t_path *del_path);

void					show_pathes(t_lemin lem, t_path **mass_pathes);

int						check_room(char *line);
int						check_line(char *line);
void					check_coords(t_lemin *lem);

void					free_lemin(t_lemin *lem);
void					free_path(t_path *path);
void					free_mass_pathes(t_path **mas, t_lemin *lem);
void					free_main_room(t_room *main_room);

t_path					**check_solution(t_lemin *lem, t_path **mass_pathes);
int						check_shortcut(t_lemin *lem);
int						isolated(t_room *room);
void					del_first_link(int id_isol_room, t_lemin *lem);
void					restore_first_link(int id_restore_room, t_lemin *lem);
void					print_color_solve(t_lemin *lem, int *a_i);
void					help_do_iteration(t_lemin *lem);
void					check_max_pathes(t_lemin *lem);

#endif
