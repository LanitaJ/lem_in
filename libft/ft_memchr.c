
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	void	*crutch;

	i = 0;
	crutch = (void*)s;
	while (i < n)
	{
		if (((const unsigned char*)s)[i] == (unsigned char)c)
			return (crutch + i);
		else if (((const unsigned char*)s)[i] == '\0' && c == '\0')
			return (crutch + i);
		i++;
	}
	return ((void*)0);
}
