
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
