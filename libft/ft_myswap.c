
#include "libft.h"

char	*ft_myswap(char *s)
{
	size_t	i;
	char	local;
	size_t	size;

	i = 0;
	size = ft_strlen(s) - 1;
	if (s)
	{
		while (i < size)
		{
			local = s[size];
			s[size] = s[i];
			s[i] = local;
			size--;
			i++;
		}
	}
	return (s);
}
