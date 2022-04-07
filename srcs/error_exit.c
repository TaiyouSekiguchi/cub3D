#include "cub3D.h"

void	error_exit(char *cmd, char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (msg == NULL)
		perror(cmd);
	else
		ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
