#include "cub3D.h"

static int	get_texture_num(t_info *info)
{
	int		texNum;

	if (info->side == 0)
	{
		if (info->rayDirX < 0)
			texNum = NORTH;
		else
			texNum = SOUTH;
	}
	else
	{
		if (info->rayDirY < 0)
			texNum = WEST;
		else
			texNum = EAST;
	}
	return (texNum);
}

static void	draw_loop(t_game *game, t_info *info, int x)
{
	int				texNum;
	double			step;
	double			texPos;
	unsigned int	color;
	int				y;

	texNum = get_texture_num(info);
	step = 1.0 * texHeight / info->lineHeight;
	texPos = (info->drawStart - game->screen_height / 2 + info->lineHeight / 2) * step;
	for (y = info->drawStart; y < info->drawEnd; y++)
	{
		info->texY = (int)texPos & (texHeight - 1);
		texPos += step;
		color = game->imgs[texNum].data[texHeight * info->texY + info->texX];
		my_mlx_pixel_put(&game->img, x, y, color);
	}
}

void	draw_texture(t_game *game, t_info *info, int x)
{
	double	wallX;

	if (info->side == 0)
		wallX = game->player.pos_y + info->perpWallDist * info->rayDirY;
	else
		wallX = game->player.pos_x + info->perpWallDist * info->rayDirX;
	wallX -= floor((wallX));
	info->texX = (int)(wallX * (double)(texWidth));
	if (info->side == 0 && info->rayDirX > 0)
		info->texX = texWidth - info->texX - 1;
	if (info->side == 1 && info->rayDirY < 0)
		info->texX = texWidth - info->texX - 1;
	draw_loop(game, info, x);
}
