/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerk <ljerk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:08:40 by ljerk             #+#    #+#             */
/*   Updated: 2020/09/01 19:39:08 by ljerk            ###   ########.fr       */
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
	ft_printf("Wrond input(incorrect chars)\n");
	exit(1);
}