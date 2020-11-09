#include "includes/lemin.h"

void	show_pathes(t_lemin lem, t_path **mass_pathes)
{
	int	i;

	i = 0;
	while (i < lem.ins)
		{
			if (lem.color == 1)
				ft_printf(CYN"Chain #%d:\n"RST, i + 1);
			else
				ft_printf("Chain #%d:\n", i + 1);
			if (lem.color == 1)
				print_path_color(mass_pathes[i]);
			else
				print_path(mass_pathes[i]);
			i++;
		}
}