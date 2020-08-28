
#include "libft.h"

void	ft_my_printlist(t_list *lst)
{
	t_list	*temp;
	int		i;

	i = 0;
	if (!lst)
		ft_putstr("Empty list");
	temp = lst;
	while (temp)
	{
		ft_putstr("Index:");
		ft_putchar('0' + i);
		ft_putchar(' ');
		ft_putstr("Content:");
		ft_putstr(temp->content);
		ft_putchar(' ');
		ft_putstr("Size:");
		ft_putnbr(temp->content_size);
		ft_putchar('\n');
		i++;
		temp = temp->next;
	}
}
