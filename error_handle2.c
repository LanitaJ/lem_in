/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:07:25 by icanker           #+#    #+#             */
/*   Updated: 2020/11/11 13:07:29 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

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

void	error_count_args(void)
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
