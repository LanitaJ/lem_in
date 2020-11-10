#include "includes/lemin.h"

static int get_aunts(char* line)
{
	int i = 0;
	while (line[i] != '\0')
	{
		if (line[i] > '9' || line[i] < '0')
			error_ant_count(line);
		i++;
	}
	if (ft_atoi(line) <= 0)
		error_ant_count(line);
	return (ft_atoi(line));
}

int parse_all(t_lemin *lem)
{
	char* line;

	get_next_line(lem->fd, &line);
	ft_printf("%s\n", line);
	lem->num_ants = get_aunts(line);
	free(line);
	get_links(lem, get_rooms(lem,line));
	if ((!lem->id_start_room && lem->id_start_room != 0) || (!lem->id_end_room && lem->id_end_room != 0))
		error_start_end();
	lem->start_room = &(lem->rooms[lem->id_start_room]);
	lem->end_room = &lem->rooms[lem->id_end_room];
	init_ants(lem);
	return (1);
}

void free_lemin(t_lemin *lem)
{
	int i;

	i = 0;
	free(lem->links);
	i = 0;
	while (i != lem->num_rooms)
	{
		free(lem->rooms[i].name);
		free_main_room(&lem->rooms[i]);
		i++;
	}
	free(lem->rooms);
	free(lem->ants);
}

void	free_mass_pathes(t_path **mas, t_lemin *lem)
{
	int	i;

	i = 0;
	while (i < lem->ins)
	{
		free(mas[i]->sh);
		//free(mas[i]->length);
		free(mas[i]);
		i++;
	}
	free(mas);
}

int main(int ac, char **av)
{
	t_lemin lem;
	t_path	**mass_pathes;

	if (ac == 3)
	{
		parse_flags(av, &lem);
		av++;
		ac--;
	}
	init_lemin(&lem, ac, av);
	parse_all(&lem);
	altor(&lem);
	init_id(&lem);
	check_coords(&lem);
	mass_pathes = find_pathes(&lem);
	if (lem.show_path == 1)
		show_pathes(lem, mass_pathes);
	count_aunts_for_pathes(mass_pathes, &lem);
	print_solve(&lem, mass_pathes);
	free_mass_pathes(mass_pathes, &lem);
	free_lemin(&lem);
	return (0);
}
