
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	size_t	k;
	size_t	j;

	i = 0;
	j = 0;
	k = 0;
	if (needle[j] == '\0' || (haystack[0] == '\0' && needle[0] == '\0'))
		return ((char*)haystack);
	while (haystack[i])
	{
		while (haystack[i + k] == needle[j] && k + i < len && needle[j])
		{
			k++;
			j++;
		}
		if (needle[j] == '\0')
			return ((char*)haystack + i);
		j = 0;
		k = 0;
		i++;
	}
	return (0);
}
