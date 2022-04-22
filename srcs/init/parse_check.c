#include "cub3D.h"

void	parse_check(t_game *game)
{
	if (game->imgs[0].img == NULL
		|| game->imgs[1].img == NULL
		|| game->imgs[2].img == NULL
		|| game->imgs[3].img == NULL
		|| game->floor == -1
		|| game->ceil == -1)
		error_exit(NULL, "cub3D : Lack of file information");
}
