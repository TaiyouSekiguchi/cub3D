#include "cub3D.h"

int	main_loop(t_game *game)
{
	draw_floor_and_ceil(game);
	draw_wall(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
