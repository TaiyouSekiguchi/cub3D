#include "cub3D.h"

int		deal_key(int key_code, t_game *game)
{
	double moveSpeed;
	double rotSpeed;
	double oldDirX;
	double oldPlaneX;

	moveSpeed = 0.5;
	rotSpeed = 0.08;

	if(key_code == KEY_W)
	{
		if(game->worldMap[(int)(game->player.posX + game->player.dirX * moveSpeed)][(int)(game->player.posY)] == 0)
			game->player.posX += game->player.dirX * moveSpeed;
		if(game->worldMap[(int)(game->player.posX)][(int)(game->player.posY + game->player.dirY * moveSpeed)] == 0)
			game->player.posY += game->player.dirY * moveSpeed;
	}
	else if(key_code == KEY_S)
	{
		if(game->worldMap[(int)(game->player.posX - game->player.dirX * moveSpeed)][(int)(game->player.posY)] == 0)
			game->player.posX -= game->player.dirX * moveSpeed;
		if(game->worldMap[(int)(game->player.posX)][(int)(game->player.posY - game->player.dirY * moveSpeed)] == 0)
			game->player.posY -= game->player.dirY * moveSpeed;
	}
	else if(key_code == KEY_D || key_code == KEY_RIGHT)
	{
		oldDirX = game->player.dirX;
		game->player.dirX = game->player.dirX * cos(-rotSpeed) - game->player.dirY * sin(-rotSpeed);
		game->player.dirY = oldDirX * sin(-rotSpeed) + game->player.dirY * cos(-rotSpeed);
		oldPlaneX = game->player.planeX;
		game->player.planeX = game->player.planeX * cos(-rotSpeed) - game->player.planeY * sin(-rotSpeed);
		game->player.planeY = oldPlaneX * sin(-rotSpeed) + game->player.planeY * cos(-rotSpeed);
	}
	else if(key_code == KEY_A || key_code == KEY_LEFT)
	{
		oldDirX = game->player.dirX;
		game->player.dirX = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
		game->player.dirY = oldDirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed);
		oldPlaneX = game->player.planeX;
		game->player.planeX = game->player.planeX * cos(rotSpeed) - game->player.planeY * sin(rotSpeed);
		game->player.planeY = oldPlaneX * sin(rotSpeed) + game->player.planeY * cos(rotSpeed);
	}
	else if (key_code == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	return (0);
}
