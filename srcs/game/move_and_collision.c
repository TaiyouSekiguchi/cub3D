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

void	move_x(t_game *game, double dir_x, double moveSpeed)
{
	while (collision_check(game, game->player.pos_x + dir_x * moveSpeed, game->player.pos_y))
	{
		moveSpeed /= 2;
		if (moveSpeed < 0.1)
			return ;
	}

	game->player.pos_x += dir_x * moveSpeed;
}

void	move_y(t_game *game, double dir_y, double moveSpeed)
{
	while (collision_check(game, game->player.pos_x, game->player.pos_y + dir_y * moveSpeed))
	{
		moveSpeed /= 2;
		if (moveSpeed < 0.1)
			return ;
	}

	game->player.pos_y += dir_y * moveSpeed;
}
