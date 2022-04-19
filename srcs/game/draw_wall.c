#include "cub3D.h"

static void	init_part(t_game *game, t_info *info, int x)
{
	info->cameraX = 2 * x / (double)game->screen_width - 1;
	info->rayDirX = game->player.dir_x + game->player.plane_x * info->cameraX;
	info->rayDirY = game->player.dir_y + game->player.plane_y * info->cameraX;
	info->mapX = (int)game->player.pos_x;
	info->mapY = (int)game->player.pos_y;
	info->deltaDistX = fabs(1 / info->rayDirX);
	info->deltaDistY = fabs(1 / info->rayDirY);
}

static void	get_side_dist(t_game *game, t_info *info)
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

static void	perform_dda(t_game *game, t_info *info)
{
	int	hit;

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

static void	caluculate_part(t_game *game, t_info *info)
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

void	draw_wall(t_game *game)
{
	t_info	info;
	int		x;

	for (x = 0; x < game->screen_width; x++)
	{
		init_part(game, &info, x);
		get_side_dist(game, &info);
		perform_dda(game, &info);
		caluculate_part(game, &info);
		draw_texture(game, &info, x);
	}
}
