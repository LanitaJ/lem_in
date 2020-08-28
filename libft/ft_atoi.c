/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:13:46 by ggeri             #+#    #+#             */
/*   Updated: 2019/09/15 20:11:36 by ggeri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int					neg;
	int					c;
	unsigned long long	res;

	c = 0;
	res = 0;
	neg = 1;
	while (*str == ' ' || *str == '\n' || *str == '\f' || *str == '\r' ||\
			*str == '\t' || *str == '\v')
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		c++;
		res = res * 10 + (*str - '0');
		if ((res >= 9223372036854775807 && neg == 1) || c >= 20)
			return (-1);
		if (res > 9223372036854775807 && neg == -1)
			return (0);
		str++;
	}
	return (res * neg);
}
