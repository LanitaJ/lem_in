
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *temp;
	t_list *temp1;

	temp = lst;
	temp1 = temp;
	if (lst && f)
	{
		while (temp)
		{
			temp1 = temp->next;
			f(temp);
			temp = temp1;
		}
	}
}
