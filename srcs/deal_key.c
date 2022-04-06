#include "cub3D.h"

int		deal_key(int key_code, t_game *game)
{
	double moveSpeed;
	double rotSpeed;

	moveSpeed = 0.5;
	rotSpeed = 0.08;

	if(key_code == KEY_W)
	{
		if(game->worldMap[(int)(game->player.posX + game->player.dirX * moveSpeed)][(int)(game->player.posY)] == 0)
			game->player.posX += game->player.dirX * moveSpeed;
		if(game->worldMap[(int)(game->player.posX)][(int)(game->player.posY + game->player.dirY * moveSpeed)] == 0)
			game->player.posY += game->player.dirY * moveSpeed;
	}
	if(key_code == KEY_S)
	{
		if(game->worldMap[(int)(game->player.posX - game->player.dirX * moveSpeed)][(int)(game->player.posY)] == 0)
			game->player.posX -= game->player.dirX * moveSpeed;
		if(game->worldMap[(int)(game->player.posX)][(int)(game->player.posY - game->player.dirY * moveSpeed)] == 0)
			game->player.posY -= game->player.dirY * moveSpeed;
	}
	if(key_code == KEY_D || key_code == KEY_RIGHT)
	{
		double oldDirX = game->player.dirX;
		game->player.dirX = game->player.dirX * cos(-rotSpeed) - game->player.dirY * sin(-rotSpeed);
		game->player.dirY = oldDirX * sin(-rotSpeed) + game->player.dirY * cos(-rotSpeed);
		double oldPlaneX = game->player.planeX;
		game->player.planeX = game->player.planeX * cos(-rotSpeed) - game->player.planeY * sin(-rotSpeed);
		game->player.planeY = oldPlaneX * sin(-rotSpeed) + game->player.planeY * cos(-rotSpeed);
	}
	if(key_code == KEY_A || key_code == KEY_LEFT)
	{
		double oldDirX = game->player.dirX;
		game->player.dirX = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
		game->player.dirY = oldDirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed);
		double oldPlaneX = game->player.planeX;
		game->player.planeX = game->player.planeX * cos(rotSpeed) - game->player.planeY * sin(rotSpeed);
		game->player.planeY = oldPlaneX * sin(rotSpeed) + game->player.planeY * cos(rotSpeed);
	}
	if (key_code == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	return (0);
}
