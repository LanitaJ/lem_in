/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:02:01 by icanker           #+#    #+#             */
/*   Updated: 2020/08/28 13:02:01 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	length;

	i = 0;
	j = 0;
	length = 0;
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0')
		j++;
	if (i >= size)
		return (j + size);
	while (i < size - 1 && dst[i])
		i++;
	while (i + length < size - 1 && src[length])
	{
		dst[i + length] = src[length];
		length++;
	}
	dst[i + length] = '\0';
	return (i + j);
}
