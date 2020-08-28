/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icanker <icanker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:58:31 by icanker           #+#    #+#             */
/*   Updated: 2020/08/28 12:58:31 by icanker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp;
	t_list	*temp1;

	temp = *alst;
	temp1 = *alst;
	while (temp)
	{
		temp = temp1->next;
		del(temp1->content, temp1->content_size);
		free(temp1);
		temp1 = temp;
	}
	*alst = (void*)0;
}
