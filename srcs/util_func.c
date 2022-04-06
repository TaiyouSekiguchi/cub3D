#include "cub3D.h"

int		my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int		my_close(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}
