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
	exit(0);
}

void 	error_maloc()
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

void	error_fd()
{
	ft_printf("Fd error\n");
	exit(1);
}
