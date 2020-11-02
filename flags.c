#include "includes/lemin.h"

void	find_flags(char ***av, t_lemin *lem)
{

	//ft_printf("%s", **av);
	if (ft_strequ(**av, "-c"))
	{
		lem->color = 1;
		(*av)++;
		find_flags(av, lem);
	}
	if (ft_strequ(**av, "-f"))
	{
		lem->bonus_fd = 1;
		(*av)++;
		find_flags(av, lem);
	}
	if (ft_strequ(**av, "-e"))
	{
		lem->error = 1;
		(*av)++;
		find_flags(av, lem);
	}
	if (ft_strequ(**av, "-p"))
	{
		lem->show_path = 1;
		(*av)++;
		find_flags(av, lem);
	}
}