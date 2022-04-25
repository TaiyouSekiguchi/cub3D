/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:58:52 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/04/25 23:58:53 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	key_w_or_s(int key_code, t_game *game, double move_speed)
{
	int	flag;

	if (key_code == KEY_W)
		flag = 1;
	else
		flag = -1;
	move_x(game, game->player.dir_x * flag, move_speed);
	move_y(game, game->player.dir_y * flag, move_speed);
}

static void	key_a_or_d(int key_code, t_game *game, double move_speed)
{
	double	ver_x;
	double	ver_y;

	if (key_code == KEY_A)
	{
		ver_x = game->player.dir_y * -1;
		ver_y = game->player.dir_x;
	}
	else
	{
		ver_x = game->player.dir_y;
		ver_y = game->player.dir_x * -1;
	}
	move_x(game, ver_x, move_speed);
	move_y(game, ver_y, move_speed);
}

static void	key_left_or_right(int key_code, t_player *player)
{
	double	rot;
	double	old_dir_x;
	double	old_plane_x;

	rot = 0.08;
	if (key_code == KEY_RIGHT)
		rot *= -1;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot) - player->dir_y * sin(rot);
	player->dir_y = old_dir_x * sin(rot) + player->dir_y * cos(rot);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot) - player->plane_y * sin(rot);
	player->plane_y = old_plane_x * sin(rot) + player->plane_y * cos(rot);
}

int	deal_key(int key_code, t_game *game)
{
	double	move_speed;

	move_speed = 0.5;
	if (key_code == KEY_W || key_code == KEY_S)
		key_w_or_s(key_code, game, move_speed);
	else if (key_code == KEY_A || key_code == KEY_D)
		key_a_or_d(key_code, game, move_speed);
	else if (key_code == KEY_LEFT || key_code == KEY_RIGHT)
		key_left_or_right(key_code, &game->player);
	else if (key_code == KEY_ESC)
	{
		game_free(game);
		exit(0);
	}
	return (0);
}
