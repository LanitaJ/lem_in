/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:58:20 by icanker           #+#    #+#             */
/*   Updated: 2020/08/28 12:58:20 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*temp;
	int		size;

	size = ft_mylengthofnum(n) + 1;
	temp = malloc(sizeof(char) * size);
	if (!temp)
		return ((void*)0);
	temp[size - 1] = '\0';
	ft_fillmynbr(temp, n, size - 1);
	return (temp);
}
