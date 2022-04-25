#include "cub3D.h"

static int	get_texture_num(t_info *info)
{
	int	tex_num;

	if (info->side == 0)
	{
		if (info->raydir_x < 0)
			tex_num = NORTH;
		else
			tex_num = SOUTH;
	}
	else
	{
		if (info->raydir_y < 0)
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
	step = 1.0 * TEXHEIGHT / info->line_height;
	tes_pos = (info->draw_start - h / 2 + info->line_height / 2) * step;
	y = info->draw_start;
	while (y < info->draw_end)
	{
		info->tex_y = (int)tes_pos & (TEXHEIGHT - 1);
		tes_pos += step;
		color = game->imgs[tex_num].data[TEXHEIGHT * info->tex_y + info->tex_x];
		my_mlx_pixel_put(&game->img, x, y, color);
		y++;
	}
}

void	draw_texture(t_game *game, t_info *info, int x)
{
	double	wall_x;

	if (info->side == 0)
		wall_x = game->player.pos_y + info->perpwalldist * info->raydir_y;
	else
		wall_x = game->player.pos_x + info->perpwalldist * info->raydir_x;
	wall_x -= floor((wall_x));
	info->tex_x = (int)(wall_x * (double)(TEXWIDTH));
	if (info->side == 0 && info->raydir_x > 0)
		info->tex_x = TEXWIDTH - info->tex_x - 1;
	if (info->side == 1 && info->raydir_y < 0)
		info->tex_x = TEXWIDTH - info->tex_x - 1;
	draw_loop(game, info, x, game->screen_height);
}
