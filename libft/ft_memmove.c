
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*s1;
	const unsigned char	*s2;

	i = -1;
	if (dst == NULL && src == NULL)
		return (NULL);
	s1 = (unsigned char*)dst;
	s2 = (const unsigned char*)src;
	if (s1 > s2)
		while ((int)(--len) >= 0)
			*(s1 + len) = *(s2 + len);
	else
		while (++i < len)
			*(s1 + i) = *(s2 + i);
	return (dst);
}
