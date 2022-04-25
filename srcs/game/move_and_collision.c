#include "cub3D.h"

static int	collision_check(t_game *game, double pos_x, double pos_y)
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

void	move_x(t_game *game, double dir_x, double move_speed)
{
	double	pos_x;
	double	pos_y;

	pos_x = game->player.pos_x;
	pos_y = game->player.pos_y;
	while (collision_check(game, pos_x + dir_x * move_speed, pos_y))
	{
		move_speed /= 2;
		if (move_speed < 0.3)
			return ;
	}
	game->player.pos_x += dir_x * move_speed;
}

void	move_y(t_game *game, double dir_y, double move_speed)
{
	double	pos_x;
	double	pos_y;

	pos_x = game->player.pos_x;
	pos_y = game->player.pos_y;
	while (collision_check(game, pos_x, pos_y + dir_y * move_speed))
	{
		move_speed /= 2;
		if (move_speed < 0.3)
			return ;
	}
	game->player.pos_y += dir_y * move_speed;
}
