/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:02:39 by icanker           #+#    #+#             */
/*   Updated: 2020/08/28 13:02:39 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = (char*)malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (0);
	while (i < size + 1)
	{
		temp[i] = '\0';
		i++;
	}
	return (temp);
}
