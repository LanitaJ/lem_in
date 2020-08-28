/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:01:50 by icanker           #+#    #+#             */
/*   Updated: 2020/08/28 13:01:50 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;
	unsigned int	loc;

	i = 0;
	loc = 0;
	if (s && f)
	{
		while (s[i])
		{
			loc = i;
			f(i, &s[loc]);
			i++;
		}
	}
}
