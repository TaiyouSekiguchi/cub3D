#include "cub3D.h"

static void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->screen_width, game->screen_height, "cub3D");
}

static void	player_init(t_game *game)
{
	game->player.pos_x = 0;
	game->player.pos_y = 0;
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
}

static void	img_init(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, game->screen_width, game->screen_height);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_len, &game->img.endian);
}

void	game_init(t_game *game)
{
	game->screen_width = 640;
	game->screen_height = 480;

	window_init(game);
	player_init(game);
	img_init(game);

	game->imgs[0].img = NULL;
	game->imgs[1].img = NULL;
	game->imgs[2].img = NULL;
	game->imgs[3].img = NULL;

	game->floor = -1;
	game->ceil = -1;
}
