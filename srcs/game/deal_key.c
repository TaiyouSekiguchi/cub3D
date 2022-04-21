#include "cub3D.h"

static void	key_w_or_s(int key_code, t_game *game, double moveSpeed)
{
	int	flag;

	if(key_code == KEY_W)
		flag = 1;
	else
		flag = -1;
	move_x(game, game->player.dir_x * flag, moveSpeed);
	move_y(game, game->player.dir_y * flag, moveSpeed);
}

static void	key_a_or_d(int key_code, t_game *game, double moveSpeed)
{
	double	ver_x;
	double	ver_y;

	if(key_code == KEY_A)
	{
		ver_x = game->player.dir_y * -1;
		ver_y = game->player.dir_x;
	}
	else
	{
		ver_x = game->player.dir_y;
		ver_y = game->player.dir_x * -1;
	}
	move_x(game, ver_x, moveSpeed);
	move_y(game, ver_y, moveSpeed);
}

static void	key_left_or_right(int key_code, t_game *game, double rotSpeed)
{
	double	old_dir_x;
	double	old_plane_x;

	if(key_code == KEY_RIGHT)
		rotSpeed *= -1;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rotSpeed) - game->player.dir_y * sin(rotSpeed);
	game->player.dir_y = old_dir_x * sin(rotSpeed) + game->player.dir_y * cos(rotSpeed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rotSpeed) - game->player.plane_y * sin(rotSpeed);
	game->player.plane_y = old_plane_x * sin(rotSpeed) + game->player.plane_y * cos(rotSpeed);
}

int		deal_key(int key_code, t_game *game)
{
	double	moveSpeed;
	double	rotSpeed;

	moveSpeed = 0.5;
	rotSpeed = 0.08;
	if(key_code == KEY_W || key_code == KEY_S)
		key_w_or_s(key_code, game, moveSpeed);
	else if (key_code == KEY_A || key_code == KEY_D)
		key_a_or_d(key_code, game, moveSpeed);
	else if (key_code == KEY_LEFT || key_code == KEY_RIGHT)
		key_left_or_right(key_code, game, rotSpeed);
	else if (key_code == KEY_ESC)
	{
		game_free(game);
		exit(0);
	}
	return (0);
}
