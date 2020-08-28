
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*temp;

	i = 0;
	temp = (void*)malloc(size);
	if (!temp)
		return (0);
	while (i < size)
	{
		((char*)temp)[i] = 0;
		i++;
	}
	return (temp);
}
