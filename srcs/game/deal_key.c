#include "cub3D.h"

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
		if(game->world_map[(int)(game->player.pos_x + game->player.dir_x * moveSpeed)][(int)(game->player.pos_y)] == 0)
			game->player.pos_x += game->player.dir_x * moveSpeed;
		if(game->world_map[(int)(game->player.pos_x)][(int)(game->player.pos_y + game->player.dir_y * moveSpeed)] == 0)
			game->player.pos_y += game->player.dir_y * moveSpeed;
	}
	else if(key_code == KEY_S)
	{
		if(game->world_map[(int)(game->player.pos_x - game->player.dir_x * moveSpeed)][(int)(game->player.pos_y)] == 0)
			game->player.pos_x -= game->player.dir_x * moveSpeed;
		if(game->world_map[(int)(game->player.pos_x)][(int)(game->player.pos_y - game->player.dir_y * moveSpeed)] == 0)
			game->player.pos_y -= game->player.dir_y * moveSpeed;
	}
	else if (key_code == KEY_A)
	{
		ver_x = game->player.dir_y * -1;
		ver_y = game->player.dir_x;
		if(game->world_map[(int)(game->player.pos_x + ver_x * moveSpeed)][(int)(game->player.pos_y)] == 0)
			game->player.pos_x += ver_x * moveSpeed;
		if(game->world_map[(int)(game->player.pos_x)][(int)(game->player.pos_y + ver_y * moveSpeed)] == 0)
			game->player.pos_y += ver_y * moveSpeed;
	}
	else if (key_code == KEY_D)
	{
		ver_x = game->player.dir_y;
		ver_y = game->player.dir_x * -1;
		if(game->world_map[(int)(game->player.pos_x + ver_x * moveSpeed)][(int)(game->player.pos_y)] == 0)
			game->player.pos_x += ver_x * moveSpeed;
		if(game->world_map[(int)(game->player.pos_x)][(int)(game->player.pos_y + ver_y * moveSpeed)] == 0)
			game->player.pos_y += ver_y * moveSpeed;
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
		//mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	//mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
