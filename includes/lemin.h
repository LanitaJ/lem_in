/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerk <ljerk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:11:57 by ljerk             #+#    #+#             */
/*   Updated: 2020/09/28 18:48:43 by ljerk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char*				name;
	int					x;
	int					y;
	struct s_room*		*n_rooms;
	int					*blocks;	//0 - связь есть 1 - связи нет 
	int					num_links;
	int					depth;		//глубина комнаты (0 - старт, 2147483647 - конец)
	int					visited;	//метка, что комнату посетили
	int					id;
}						t_room;

typedef struct			s_path
{
	t_room				**sh;		//путь
	int					length;		//длина пути
	int					count_ants;	//количество муравьев на пути
}						t_path;

typedef	struct			s_lemin
{
	int					num_links;
	int					num_ants;
	int					num_rooms;
	int					fd;
	int					id_start_room;
	int					id_end_room;
	int					check_start_kol;
	int 				check_end_kol;
	int					max_pathes;
	int					ins;
	int					error;		//флаг -e
	int					color;		//флаг -c
	int					bonus_fd;	//флаг -f
	int					show_path;	//флаг -p
	t_room*				rooms;
	t_room				*start_room;
	t_room				*end_room;
	t_link*				links;
}						t_lemin;

void					get_link(char* line, t_link *l, t_lemin *lem);
int						add_link(t_lemin *lem, char* line);
int						parse_links(t_lemin *lem);
int						create_link(t_room *main_room, t_link *link, t_lemin *lem);
int						check_link(char *line);
int						get_links(t_lemin *lem, char *line);
char					*get_rooms(t_lemin *lem, char* line);
int						get_room(char* line, t_room *room);
int						add_room(t_lemin *lem, char* line);
void					exit_get_room(char* line);
int						get_first_room(char* line, t_link *l);
int						get_second_room(char *line, t_link *l);

int						numlen(int nbr);
int						check_room(char* line);
int						check_line(char* line);
int						compare(t_lemin *lem, char* str);//return number of equivalent char* with rooms
t_room					*name_to_room(char *name, t_lemin *lem);
int						add_room_to_room(t_room *main_room, char* name_add, t_lemin* lem);
int						altor(t_lemin *lem);

//Error handler
void					error_ant_count(char *line);
void					error_trash(char *line);
void					error_memmory(char *line);
void					error_map(char *line);
void					error_link(char *line);

void					find_flags(char ***av, t_lemin *lem);

//Solver
t_path					**find_pathes(t_lemin *lem);
int						bfs(t_lemin *lem);

//функция вывода карты в консоль (Вспомогательная функция. После окончания проекта удалить)
void					output_map(t_lemin lem);
void					print_path(t_path *path);
void					print_path_color(t_path *path);



//функция выбора случаев
void					path_type(t_path **mas, t_lemin *lem, t_path *path1, t_path *path2);

void					del_path(t_path *path);

//do_types
void					do_type1(t_lemin *lem, t_path **mas, t_path *path1, t_path *path2);
void					do_type2_3(t_lemin *lem, t_path **mas, t_path *path);

//free
void					free_path(t_path *path);
void					free_room(t_room *room);

