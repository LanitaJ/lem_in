#include "includes/lemin.h"

void	free_path(t_path *path)
{
	free(path->sh);
	free(path);
}

void	do_type1(t_lemin *lem, t_path **mas, t_path *path1, t_path *path2)
{
	mas[lem->ins] = path1;
	mas[lem->ins + 1] = path2;
    lem->ins += 2;
	del_path(path1);
	del_path(path2);
    lem->max_pathes--;	
}

void	do_type2_3(t_lemin *lem, t_path **mas, t_path *path, t_path *d_path)
{
	mas[lem->ins] = path;
	lem->ins++;
	free_path(d_path);
	del_path(path);
}