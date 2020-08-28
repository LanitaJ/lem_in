
#include "libft.h"

int		ft_my_count_c_words(char const *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (s)
	{
		while (*s != '\0')
		{
			i = 0;
			while (*s == c)
				s++;
			while (*s != c && *s != '\0')
			{
				i = 1;
				s++;
			}
			if (i == 1)
				count++;
		}
	}
	return (count);
}
