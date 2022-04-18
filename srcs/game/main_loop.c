#include "cub3D.h"

void	init_part(t_game *game, t_info *info, int x)
{
	info->cameraX = 2 * x / (double)game->screen_width - 1;

	info->rayDirX = game->player.dir_x + game->player.plane_x * info->cameraX;
	info->rayDirY = game->player.dir_y + game->player.plane_y * info->cameraX;

	info->mapX = (int)game->player.pos_x;
	info->mapY = (int)game->player.pos_y;

	info->deltaDistX = fabs(1 / info->rayDirX);
	info->deltaDistY = fabs(1 / info->rayDirY);
}

void	get_side_dist(t_game *game, t_info *info)
{
	if (info->rayDirX < 0)
	{
		info->stepX = -1;
		info->sideDistX = (game->player.pos_x - info->mapX) * info->deltaDistX;
	}
	else
	{
		info->stepX = 1;
		info->sideDistX = (info->mapX + 1.0 - game->player.pos_x) * info->deltaDistX;
	}
	if (info->rayDirY < 0)
	{
		info->stepY = -1;
		info->sideDistY = (game->player.pos_y - info->mapY) * info->deltaDistY;
	}
	else
	{
		info->stepY = 1;
		info->sideDistY = (info->mapY + 1.0 - game->player.pos_y) * info->deltaDistY;
	}
}

void	perform_dda(t_game *game, t_info *info)
{
	int		hit;

	hit = 0;
	while (hit == 0)
	{
		if (info->sideDistX < info->sideDistY)
		{
			info->sideDistX += info->deltaDistX;
			info->mapX += info->stepX;
			info->side = 0;
		}
		else
		{
			info->sideDistY += info->deltaDistY;
			info->mapY += info->stepY;
			info->side = 1;
		}
		if (game->world_map[info->mapX][info->mapY] > 0)
			hit = 1;
	}
}

void	caluculate_part(t_game *game, t_info *info)
{
	if (info->side == 0)
		info->perpWallDist = (info->mapX - game->player.pos_x + (1 - info->stepX) / 2) / info->rayDirX;
	else
		info->perpWallDist = (info->mapY - game->player.pos_y + (1 - info->stepY) / 2) / info->rayDirY;
	info->lineHeight = (int)(game->screen_height / info->perpWallDist);
	info->drawStart = -info->lineHeight / 2 + game->screen_height / 2;
	if (info->drawStart < 0)
		info->drawStart = 0;
	info->drawEnd = info->lineHeight / 2 + game->screen_height / 2;
	if (info->drawEnd >= game->screen_height)
		info->drawEnd = game->screen_height - 1;
}

int		get_texture_num(t_info *info)
{
	int		texNum;

	if (info->side == 0)
	{
		if (info->rayDirX < 0)
			texNum = 1;
		else
			texNum = 3;
	}
	else
	{
		if (info->rayDirY < 0)
			texNum = 2;
		else
			texNum = 0;
	}
	return (texNum);
}

void	draw_loop(t_game *game, t_info *info, unsigned int texture[4][texWidth * texHeight], int x, int texX)
{
	double			step;
	double			texPos;
	int				y;
	int				texY;
	unsigned int	color;
	int		texNum;

	texNum = get_texture_num(info);
	step = 1.0 * texHeight / info->lineHeight;
	texPos = (info->drawStart - game->screen_height / 2 + info->lineHeight / 2) * step;
	for (y = info->drawStart; y < info->drawEnd; y++)
	{
		texY = (int)texPos & (texHeight - 1);
		texPos += step;
		color = game->imgs[texNum].data[texHeight * texY + texX];
		//color = texture[texNum][texHeight * texY + texX];
		if (info->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&game->img, x, y, color);
	}
}

void	draw_texture(t_game *game, t_info *info, unsigned int texture[4][texWidth * texHeight], int x)
{
	double	wallX;
	int		texX;


	if (info->side == 0)
		wallX = game->player.pos_y + info->perpWallDist * info->rayDirY;
	else
		wallX = game->player.pos_x + info->perpWallDist * info->rayDirX;
	wallX -= floor((wallX));

	texX = (int)(wallX * (double)(texWidth));
	if (info->side == 0 && info->rayDirX > 0)
		texX = texWidth - texX - 1;
	if (info->side == 1 && info->rayDirY < 0)
		texX = texWidth - texX - 1;
	draw_loop(game, info, texture, x, texX);
}

int		main_loop(t_game *game)
{
	t_info			info;
	int				x;
	int				y;
	unsigned int	texture[4][texWidth * texHeight];

	for (x = 0; x < 4; x++)
	{
		for (y = 0; y < texWidth * texHeight; y++)
		{
			texture[x][y] = game->imgs[x].data[y];
		}
	}

	//floor and ceil
	draw_floor_and_ceil(game);

	//wall
	for (x = 0; x < game->screen_width; x++)
	{
		init_part(game, &info, x);
		get_side_dist(game, &info);
		perform_dda(game, &info);
		caluculate_part(game, &info);
		draw_texture(game, &info, texture, x);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
