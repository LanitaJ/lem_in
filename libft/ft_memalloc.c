/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:59:04 by icanker           #+#    #+#             */
/*   Updated: 2020/08/28 12:59:04 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*temp;

	i = 0;
	temp = (void*)malloc(size);
	if (!temp)
		return (0);
	while (i < size)
	{
		((char*)temp)[i] = 0;
		i++;
	}
	return (temp);
}
