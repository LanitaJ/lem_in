
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;
	unsigned int	loc;

	i = 0;
	loc = 0;
	if (s && f)
	{
		while (s[i])
		{
			loc = i;
			f(i, &s[loc]);
			i++;
		}
	}
}
