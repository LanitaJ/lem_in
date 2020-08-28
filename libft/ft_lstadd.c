
#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new1)
{
	if (new1 != (void*)0)
	{
		new1->next = *alst;
		*alst = new1;
	}
}
