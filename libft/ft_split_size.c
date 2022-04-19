#include "libft.h"

size_t	ft_split_size(char **split)
{
	size_t	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}
