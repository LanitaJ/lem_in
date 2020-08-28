/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:02:14 by icanker           #+#    #+#             */
/*   Updated: 2020/08/28 13:02:14 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	loc;
	char			*temp;

	i = 0;
	loc = 0;
	temp = (void*)0;
	if (s && f)
	{
		temp = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
		if (!temp)
			return ((void*)0);
		while (i < ft_strlen(s))
		{
			loc = i;
			temp[i] = f(i, s[i]);
			i++;
		}
		temp[i] = '\0';
	}
	return (temp);
}
