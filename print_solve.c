#include "includes/lemin.h"

void count_aunts_for_pathes(t_path* *mass_pathes, t_lemin *lem)
{
	int i;

	i = 0;
	while(i < lem->ins)
		mass_pathes[i++]->count_ants = 0;
	while (1)
	{
		i = 0;
		if (i == lem->ins)
			return ;
		while(i != lem->ins)
		{
			if (lem->UsableAunts >= lem->num_ants)
				return ;
			if (mass_pathes[i]->length + mass_pathes[i]->count_ants < lem->stage)
			{
				mass_pathes[i]->count_ants++;
				lem->UsableAunts++;
			}
			i++;
		}
		lem->stage++;
	}
}

t_room *FindNext(t_path* path, t_room* ThisRoom)
{
	int i;

	i = 0;
	while (i != path->length - 1)
	{
		if (!strcmp(path->sh[i]->name, ThisRoom->name))
			return (path->sh[i + 1]);
		i++;
	}
	return (ThisRoom);
}

int count_iterations(t_lemin *lem, t_path* *mass_pathes)
{
	int i;
	int max;

	i = 0;
	max = -1;
	while (i != lem->ins)
	{
		if (max < mass_pathes[i]->length - 1 + mass_pathes[i]->count_ants && \
				mass_pathes[i]->count_ants != 0)
			max = mass_pathes[i]->length - 1 + mass_pathes[i]->count_ants;
		i++;
	}
	//ft_printf("max %d\n", max);
	return (max);
}

static void do_iteration(int *j, t_lemin *lem, t_path* *mass_pathes)
{
	int ant_i;

	ant_i = 0;
	while(lem->ants[ant_i].VisitedRoom && ant_i <= lem->num_ants - 1)
	{
		if (ft_strcmp(lem->ants[ant_i].VisitedRoom->name,lem->end_room->name))
		{
			lem->ants[ant_i].VisitedRoom = FindNext(lem->ants[ant_i].UsedPath, lem->ants[ant_i].VisitedRoom);
			ft_printf("L%d-%s ", lem->ants[ant_i].nbr, lem->ants[ant_i].VisitedRoom->name);
		}
		ant_i++;
	}
	*j = 0;
	while(*j != lem->ins && ant_i <= lem->num_ants - 1)
	{
		if (mass_pathes[*j]->count_ants > 0)
		{
			lem->ants[ant_i].UsedPath = mass_pathes[*j];
			lem->ants[ant_i].VisitedRoom = mass_pathes[*j]->sh[1];
			mass_pathes[*j]->count_ants -= 1;
			ft_printf("L%d-%s ", lem->ants[ant_i].nbr, lem->ants[ant_i].VisitedRoom->name);
			ant_i++;
		}
		(*j)++;
	}
};

void print_solve(t_lemin *lem, t_path* *mass_pathes)
{
	int i;
	int max;
	int j;

	max = count_iterations(lem, mass_pathes);
	i = 0;
	ft_bzero(lem->ants, sizeof(lem->ants));
	while (i != max)
	{
		ft_putstr("\n");
		do_iteration(&j, lem, mass_pathes);
		i++;
	}
	if (lem->num_lines == 1)
		lem->color ? ft_printf(GRN"Count of lines: %d\n"RST, max) : \
						ft_printf("Count of lines: %d\n", max);
}