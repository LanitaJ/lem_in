
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c > 127 || c < 0)
		return (0);
	while (s[i])
		i++;
	if (s[i] == '\0' && c == '\0')
		return ((char*)s + i);
	i--;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char*)s + i);
		i--;
	}
	return (0);
}
