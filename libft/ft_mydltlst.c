/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mydltlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:00:05 by icanker           #+#    #+#             */
/*   Updated: 2020/08/28 13:00:05 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_mydltlst(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		free(lst);
		lst = temp->next;
		temp = temp->next;
	}
}
