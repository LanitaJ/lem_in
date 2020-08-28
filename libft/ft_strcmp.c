
#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] == s2[j] && s1[i])
	{
		i++;
		j++;
	}
	return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[j]);
}
