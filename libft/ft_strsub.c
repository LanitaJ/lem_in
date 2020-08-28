/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:03:01 by icanker           #+#    #+#             */
/*   Updated: 2020/08/28 13:03:48 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = (void*)0;
	if (s)
	{
		temp = (char*)malloc(sizeof(char) * (len + 1));
		if (!temp)
			return ((void*)0);
		while (i < len)
		{
			temp[i] = s[start];
			start++;
			i++;
		}
		temp[i] = '\0';
	}
	return (temp);
}
