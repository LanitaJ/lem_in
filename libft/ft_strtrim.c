/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:03:06 by icanker           #+#    #+#             */
/*   Updated: 2020/08/28 13:03:49 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*temp;
	size_t	count;
	size_t	k;

	k = 0;
	temp = (void*)0;
	count = ft_my_counting_of_str(s) + 1;
	if (s)
	{
		temp = (char*)malloc(sizeof(char) * (count));
		if (!temp)
			return ((void*)0);
		temp[--count] = '\0';
		count--;
		while (s[k] == ' ' || s[k] == '\t' || s[k] == '\n')
			k++;
		while ((int)count > -1)
		{
			temp[count] = s[k + count];
			count--;
		}
	}
	return (temp);
}
