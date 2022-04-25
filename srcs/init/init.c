#include "cub3D.h"

static void	window_init(t_game *game, int w, int h)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, w, h, "cub3D");
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

static void	img_init(t_game *game, t_img *img, int w, int h)
{
	int		*bpp;
	int		*line_len;
	int		*endian;

	bpp = &img->bpp;
	line_len = &img->line_len;
	endian = &img->endian;
	img->img = mlx_new_image(game->mlx, w, h);
	img->addr = mlx_get_data_addr(img->img, bpp, line_len, endian);
}

void	game_init(t_game *game, char *news)
{
	game->screen_width = 640;
	game->screen_height = 480;
	window_init(game, game->screen_width, game->screen_height);
	player_init(game);
	img_init(game, &game->img, game->screen_width, game->screen_height);
	game->imgs[0].img = NULL;
	game->imgs[1].img = NULL;
	game->imgs[2].img = NULL;
	game->imgs[3].img = NULL;
	game->floor = -1;
	game->ceil = -1;
	game->re_cnt = 20000;
	*news = '\0';
}
