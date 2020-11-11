/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:59:26 by icanker           #+#    #+#             */
/*   Updated: 2020/11/10 16:00:25 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

void	del_path(t_path *path)
{
	int	i;
	int	j;
	int k;

	i = 1;
	while (i < path->length - 1)
	{
		j = 0;
		while (j < path->sh[i]->num_links)
		{
			k = 0;
			while (path->sh[i]->n_rooms[j]->n_rooms[k]->id != path->sh[i]->id)
				k++;
			path->sh[i]->n_rooms[j]->blocks[k] = 1;
			path->sh[i]->blocks[j] = 1;
			j++;
		}
		i++;
	}
}

int		*path_to_num(t_lemin *lem, t_path *path)
{
	int	*bin_res;
	int	i;

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

int		choose_type(t_lemin *lem, t_path *path1, t_path *path2)
{
	int *bin_path1;
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
	if (sum_sochet == 2)
		return (1);
	else
		return ((sum_sochet == path1->length) ? 2 : 3);
}

void	path_type(t_path **mas, t_lemin *lem, t_path *path1, t_path *path2)
{
	int	type;

	type = choose_type(lem, path1, path2);
	if (type == 1)
		do_type1(lem, mas, path1, path2);
	else if (type == 2)
		do_type2_3(lem, mas, path1, path2);
	else
		do_type2_3(lem, mas, path2, path1);
}
