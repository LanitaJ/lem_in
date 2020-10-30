#include "includes/lemin.h"

int *path_to_num(t_lemin *lem, t_path *path)
{
    int *bin_res;   //представление результата в виде(двоичное число) массива из 0 и 1, где 1 - наличие iой комнаты в пути 
    int i;
    
    i = 0;
    if ((bin_res = (int*)ft_memalloc(sizeof(int) * lem->num_rooms)) == NULL)
        exit(1);
    while (i < path->length)
    {
        bin_res[path->sh[i]->id] = 1;
        i++;
    }
    return (bin_res);
}

int choose_type(t_lemin *lem, t_path *path1, t_path *path2)
{
    int *bin_path1; //двоичное представление путей. 0 - комната с id = i отстутствует в пути
    int *bin_path2;
    int sum_sochet;
    int i;

    bin_path1 = path_to_num(lem, path1);
    bin_path2 = path_to_num(lem, path2);
    i = 0;
    sum_sochet = 0;
    while (i < lem->num_rooms)
    {
        if ((bin_path1[i] & bin_path2[i]) == 1)
            sum_sochet++;
        i++;
    }
    free(bin_path1);
    free(bin_path2);
    if (sum_sochet == 2)//2, тк совпадают start и end
        return (1);
    else
        return ((sum_sochet == path1->length) ? 2 : 3);
}
/* 
    1 - разные пути
    2 - 2ой путь содержит полностью 1ый
    3 - пути частично пересекаются
*/
