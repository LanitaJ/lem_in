
#include "libft.h"

void	ft_memdel(void **app)
{
	if (app)
	{
		free(*app);
		*app = (void*)0;
	}
}
