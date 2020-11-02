#include "includes/lemin.h"

void	do_type1(t_lemin *lem, t_path **mas, t_path *path1, t_path *path2)
{
	mas[lem->ins] = path1;
	mas[lem->ins + 1] = path2;
    lem->ins += 2;
	del_path(path1);
	del_path(path2);
    lem->max_pathes--;	
}

void	do_type2_3(t_lemin *lem, t_path **mas, t_path *path)
{
	mas[lem->ins] = path;
	lem->ins++;
	del_path(path);
}