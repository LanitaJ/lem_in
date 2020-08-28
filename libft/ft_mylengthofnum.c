
#include "libft.h"

int		ft_mylengthofnum(int nbr)
{
	int	i;

	i = 0;
	if (nbr == -2147483648)
		return (11);
	if (nbr <= 0)
	{
		i++;
		nbr *= -1;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}
