/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:02:09 by icanker           #+#    #+#             */
/*   Updated: 2020/08/28 13:02:09 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	i;
	char			*temp;

	i = 0;
	temp = (void*)0;
	if (s && f)
	{
		temp = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
		if (!temp)
			return ((void*)0);
		while (i < ft_strlen(s))
		{
			if (f(s[i]) != 0)
				temp[i] = f(s[i]);
			i++;
		}
		temp[i] = '\0';
	}
	return (temp);
}
