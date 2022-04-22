#include "cub3D.h"

static int	get_texture_num(t_info *info)
{
	int	tex_num;

	if (info->side == 0)
	{
		if (info->rayDirX < 0)
			tex_num = NORTH;
		else
			tex_num = SOUTH;
	}
	else
	{
		if (info->rayDirY < 0)
			tex_num = WEST;
		else
			tex_num = EAST;
	}
	return (tex_num);
}

static void	draw_loop(t_game *game, t_info *info, int x, int h)
{
	int				tex_num;
	double			step;
	double			tes_pos;
	unsigned int	color;
	int				y;

	tex_num = get_texture_num(info);
	step = 1.0 * texHeight / info->lineHeight;
	tes_pos = (info->drawStart - h / 2 + info->lineHeight / 2) * step;
	y = info->drawStart;
	while (y < info->drawEnd)
	{
		info->texY = (int)tes_pos & (texHeight - 1);
		tes_pos += step;
		color = game->imgs[tex_num].data[texHeight * info->texY + info->texX];
		my_mlx_pixel_put(&game->img, x, y, color);
		y++;
	}
}

void	draw_texture(t_game *game, t_info *info, int x)
{
	double	wall_x;

	if (info->side == 0)
		wall_x = game->player.pos_y + info->perpWallDist * info->rayDirY;
	else
		wall_x = game->player.pos_x + info->perpWallDist * info->rayDirX;
	wall_x -= floor((wall_x));
	info->texX = (int)(wall_x * (double)(texWidth));
	if (info->side == 0 && info->rayDirX > 0)
		info->texX = texWidth - info->texX - 1;
	if (info->side == 1 && info->rayDirY < 0)
		info->texX = texWidth - info->texX - 1;
	draw_loop(game, info, x, game->screen_height);
}
