
#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	if (haystack[i] == '\0' && needle[j] == '\0')
		return ((char*)haystack);
	while (haystack[i])
	{
		while (haystack[i + k] == needle[j] && needle[j])
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
