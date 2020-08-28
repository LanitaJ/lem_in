
#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	char	*begin;

	begin = dst;
	while ((*dst++ = *src++) != '\0')
	{
		;
	}
	return (begin);
}
