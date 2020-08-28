
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = (void*)0;
	if (s)
	{
		temp = (char*)malloc(sizeof(char) * (len + 1));
		if (!temp)
			return ((void*)0);
		while (i < len)
		{
			temp[i] = s[start];
			start++;
			i++;
		}
		temp[i] = '\0';
	}
	return (temp);
}
