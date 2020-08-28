
#include "libft.h"

int		ft_my_counting_of_str(const char *s)
{
	int		length;
	int		k;

	k = 0;
	length = 0;
	if (s)
	{
		while (s[k] == ' ' || s[k] == '\n' || s[k] == '\t')
			k++;
		length = ft_strlen(s) - 1;
		while (s[length] == ' ' || s[length] == '\n' || s[length] == '\t')
			length--;
		length = length - k + 1;
		if (length < 0)
			length = 0;
	}
	return (length);
}
