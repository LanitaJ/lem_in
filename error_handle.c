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

void	error_link(char *line)
{
	free(line);
	ft_printf(RED"{fd}Link error\n"RST, 2);
	exit(1);
}

void	error_start_end(void)
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
