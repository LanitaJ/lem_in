
#include "libft.h"

char	*ft_fillmynbr(char *s, int nb, int size)
{
	if (nb == -2147483648)
	{
		s[0] = '-';
		s[1] = 2 + '0';
		nb = 147483648;
	}
	if (nb < 0)
	{
		s[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		s[0] = '0';
	while (nb > 0)
	{
		size--;
		s[size] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (s);
}
