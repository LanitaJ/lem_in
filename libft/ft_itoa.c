
#include "libft.h"

char	*ft_itoa(int n)
{
	char	*temp;
	int		size;

	size = ft_mylengthofnum(n) + 1;
	temp = malloc(sizeof(char) * size);
	if (!temp)
		return ((void*)0);
	temp[size - 1] = '\0';
	ft_fillmynbr(temp, n, size - 1);
	return (temp);
}
