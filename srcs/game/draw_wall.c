/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:59:13 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/04/25 23:59:15 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_part(t_game *game, t_info *info, int x)
{
	info->camera_x = 2 * x / (double)game->screen_width - 1;
	info->raydir_x = game->player.dir_x + game->player.plane_x * info->camera_x;
	info->raydir_y = game->player.dir_y + game->player.plane_y * info->camera_x;
	info->map_x = (int)game->player.pos_x;
	info->map_y = (int)game->player.pos_y;
	info->deltadist_x = fabs(1 / info->raydir_x);
	info->deltadist_y = fabs(1 / info->raydir_y);
}

static void	get_side_dist(t_player *player, t_info *info)
{
	if (info->raydir_x < 0)
	{
		info->step_x = -1;
		info->sidedist_x = (player->pos_x - info->map_x) * info->deltadist_x;
	}
	else
	{
		info->step_x = 1;
		info->sidedist_x = (info->map_x + 1.0 - player->pos_x)
			* info->deltadist_x;
	}
	if (info->raydir_y < 0)
	{
		info->step_y = -1;
		info->sidedist_y = (player->pos_y - info->map_y)
			* info->deltadist_y;
	}
	else
	{
		info->step_y = 1;
		info->sidedist_y = (info->map_y + 1.0 - player->pos_y)
			* info->deltadist_y;
	}
}

static void	perform_dda(t_game *game, t_info *info)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (info->sidedist_x < info->sidedist_y)
		{
			info->sidedist_x += info->deltadist_x;
			info->map_x += info->step_x;
			info->side = 0;
		}
		else
		{
			info->sidedist_y += info->deltadist_y;
			info->map_y += info->step_y;
			info->side = 1;
		}
		if (game->world_map[info->map_x][info->map_y] > 0)
			hit = 1;
	}
}

static void	caluc_part(t_game *game, t_info *info, double pos_x, double pos_y)
{
	double	*pwd;

	pwd = &info->perpwalldist;
	if (info->side == 0)
		*pwd = (info->map_x - pos_x + (1 - info->step_x) / 2) / info->raydir_x;
	else
		*pwd = (info->map_y - pos_y + (1 - info->step_y) / 2) / info->raydir_y;
	info->line_height = (int)(game->screen_height / info->perpwalldist);
	info->draw_start = -info->line_height / 2 + game->screen_height / 2;
	if (info->draw_start < 0)
		info->draw_start = 0;
	info->draw_end = info->line_height / 2 + game->screen_height / 2;
	if (info->draw_end >= game->screen_height)
		info->draw_end = game->screen_height - 1;
}

void	draw_wall(t_game *game)
{
	t_info	info;
	int		x;

	x = 0;
	while (x < game->screen_width)
	{
		init_part(game, &info, x);
		get_side_dist(&game->player, &info);
		perform_dda(game, &info);
		caluc_part(game, &info, game->player.pos_x, game->player.pos_y);
		draw_texture(game, &info, x);
		x++;
	}
}
