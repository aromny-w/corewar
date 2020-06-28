#include "libft.h"

void	ft_arrdel(char ***arr)
{
	size_t	i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while (*(*arr + i))
	{
		free(*(*arr + i));
		*(*arr + i) = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}