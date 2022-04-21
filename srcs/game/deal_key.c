#include "cub3D.h"

int		collision_check(t_game *game, double pos_x, double pos_y)
{
	double	x;
	double	y;

	x = pos_x - 0.1;
	while (x < pos_x + 0.1)
	{
		y = pos_y - 0.1;
		while (y < pos_y + 0.1)
		{
			if (game->world_map[(int)x][(int)y] == 1)
				return (1);
			y += 0.01;
		}
		x += 0.01;
	}
	return (0);
}

void	moving_x(t_game *game, double dir_x, double moveSpeed)
{
	while (collision_check(game, game->player.pos_x + dir_x * moveSpeed, game->player.pos_y))
	{
		moveSpeed /= 2;
		if (moveSpeed < 0.1)
			return ;
	}

	game->player.pos_x += dir_x * moveSpeed;
}

void	moving_y(t_game *game, double dir_y, double moveSpeed)
{
	while (collision_check(game, game->player.pos_x, game->player.pos_y + dir_y * moveSpeed))
	{
		moveSpeed /= 2;
		if (moveSpeed < 0.1)
			return ;
	}

	game->player.pos_y += dir_y * moveSpeed;
}

int		deal_key(int key_code, t_game *game)
{
	double	moveSpeed;
	double	rotSpeed;
	double	old_dir_x;
	double	old_plane_x;
	double	ver_x;
	double	ver_y;

	moveSpeed = 0.5;
	rotSpeed = 0.08;
	if(key_code == KEY_W)
	{
		moving_x(game, game->player.dir_x, moveSpeed);
		moving_y(game, game->player.dir_y, moveSpeed);
	}
	else if(key_code == KEY_S)
	{
		moving_x(game, -game->player.dir_x, moveSpeed);
		moving_y(game, -game->player.dir_y, moveSpeed);
	}
	else if (key_code == KEY_A)
	{
		ver_x = game->player.dir_y * -1;
		ver_y = game->player.dir_x;

		moving_x(game, ver_x, moveSpeed);
		moving_y(game, ver_y, moveSpeed);
	}
	else if (key_code == KEY_D)
	{
		ver_x = game->player.dir_y;
		ver_y = game->player.dir_x * -1;

		moving_x(game, ver_x, moveSpeed);
		moving_y(game, ver_y, moveSpeed);
	}
	else if(key_code == KEY_RIGHT)
	{
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-rotSpeed) - game->player.dir_y * sin(-rotSpeed);
		game->player.dir_y = old_dir_x * sin(-rotSpeed) + game->player.dir_y * cos(-rotSpeed);
		old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-rotSpeed) - game->player.plane_y * sin(-rotSpeed);
		game->player.plane_y = old_plane_x * sin(-rotSpeed) + game->player.plane_y * cos(-rotSpeed);
	}
	else if(key_code == KEY_LEFT)
	{
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rotSpeed) - game->player.dir_y * sin(rotSpeed);
		game->player.dir_y = old_dir_x * sin(rotSpeed) + game->player.dir_y * cos(rotSpeed);
		old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(rotSpeed) - game->player.plane_y * sin(rotSpeed);
		game->player.plane_y = old_plane_x * sin(rotSpeed) + game->player.plane_y * cos(rotSpeed);
	}
	else if (key_code == KEY_ESC)
	{
		game_free(game);
		exit(0);
	}
	return (0);
}
