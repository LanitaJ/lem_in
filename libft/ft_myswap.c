/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myswap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:00:16 by icanker           #+#    #+#             */
/*   Updated: 2020/08/28 13:00:16 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_myswap(char *s)
{
	size_t	i;
	char	local;
	size_t	size;

	i = 0;
	size = ft_strlen(s) - 1;
	if (s)
	{
		while (i < size)
		{
			local = s[size];
			s[size] = s[i];
			s[i] = local;
			size--;
			i++;
		}
	}
	return (s);
}
