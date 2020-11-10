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

void	error_ant_count(char *line)
{
	free(line);
	ft_printf(RED"{fd}Wrong count of ants\n"RST, 2);
	exit(1);
}

void	error_trash(char *line)
{
	free(line);
	ft_printf(RED"{fd}Wrong input(incorrect chars)\n"RST, 2);
	exit(1);
}

void	error_memmory(char *line)
{
	free(line);
	ft_printf(RED"{fd}Memmory error\n"RST, 2);
	exit(1);
}

void	error_map(char *line)
{
	free(line);
	ft_printf(RED"{fd}Map error\n"RST, 2);
	exit(1);
}

void	error_link(char *line)
{
	free(line);
	ft_printf(RED"{fd}Link error\n"RST, 2);
	exit(1);
}

void	error_start_end()
{
	ft_printf(RED"{fd}Start/end error\n"RST, 2);
	exit(1);
}

void	error_malloc(void)
{
	ft_printf(RED"{fd}Malloc error\n"RST, 2);
	exit(1);
}

void	error_getrooms(char *line)
{
	ft_printf(RED"{fd}Get_room error\n"RST, 2);
	free(line);
	exit(1);
}

void	error_fd(void)
{
	ft_printf(RED"{fd}Fd error\n"RST, 2);
	exit(1);
}

void	error_coord(t_lemin *lem, t_room *r1, t_room *r2)
{
	free_lemin(lem);
	ft_printf(RED"{fd}Duplicate coords name: %s x: %d y: %d and name:\
		%s x: %d y: %d"RST, 2, r1->name, r1->x, r1->y, r2->name, r2->x, r2->y);
	exit(1);
}

void	error_count_args()
{
	ft_printf(RED"{fd}Usage:./lem-in < name.map or ./lem-in name.map\n"RST, 2);
	exit(1);
}

void	error_isolated_start(t_lemin *lem)
{
	ft_printf(RED"{fd}Start isolated\n"RST, 2);
	free_lemin(lem);
	exit(1);
}
