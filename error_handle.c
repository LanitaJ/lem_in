/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerk <ljerk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:08:40 by ljerk             #+#    #+#             */
/*   Updated: 2020/09/04 18:51:49 by ljerk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

void error_ant_count(char *line)
{
	free(line);
	ft_printf("Wrong count of ants\n");
	exit(1);
}

void error_trash(char *line)
{
	free(line);
	ft_printf("Wrong input(incorrect chars)\n");
	exit(1);
}

void error_memmory(char *line)
{
	free(line);
	ft_printf("Memmory error\n");
	exit(1);
}

void error_map(char *line)
{
	free(line);
	ft_printf("Map error\n");
	exit(1);
}

void	error_link(char *line)
{
	free(line);
	ft_printf("Link error\n");
	exit(1);
}

void	error_start_end()
{
	ft_putstr("Start/end error\n");
	exit(1);
}

void 	error_malloc(void)
{
	ft_putstr("Malloc error\n");
	exit (1);
}

void	error_getrooms(char *line)
{
	ft_putstr("Get_room error\n");
	free(line);
	exit(1);
}

void	error_fd(void)
{
	ft_printf("Fd error\n");
	exit(1);
}

void	error_coord(t_lemin *lem, t_room *r1, t_room *r2)
{
	free_lemin(lem);
	ft_printf("Duplicate coords name: %s x: %d y: %d and name: %s x: %d y: %d",\
		r1->name, r1->x, r1->y, r2->name, r2->x, r2->y);
	exit(1);
}

void error_count_args()
{
	ft_printf("Usage: ./lem-in < name.map or ./lem-in name.map\n");
	exit(1);
}