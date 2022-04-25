#include "cub3D.h"

void	decide_direction(t_game *game)
{
	double	direction;
	double	old_dir_x;
	double	old_plane_x;

	if (game->news != 'N')
	{
		if (game->news == 'E')
			direction = PI / 2;
		else if (game->news == 'S')
			direction = PI;
		else
		//else if (game->news == 'W')
			direction = PI * 3 / 2;
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x
			* cos(-direction) - game->player.dir_y * sin(-direction);
		game->player.dir_y = old_dir_x * sin(-direction)
			+ game->player.dir_y * cos(-direction);
		old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x
			* cos(-direction) - game->player.plane_y * sin(-direction);
		game->player.plane_y = old_plane_x * sin(-direction)
			+ game->player.plane_y * cos(-direction);
	}
}

void	file_read_result(t_game *game)
{
	printf("player pos_x  : %f\n", game->player.pos_x);
	printf("player pos_y  : %f\n", game->player.pos_y);
	printf("screen_width  : %d\n", game->screen_width);
	printf("screen_height : %d\n", game->screen_height);
	printf("floor         : %d\n", game->floor);
	printf("ceil          : %d\n", game->ceil);
}

int	main(int argc, char *argv[])
{
	t_game	game;
	t_list	*list;

	if (argc != 2)
		error_exit(NULL, "cub3d : ./cub3D file_name.cub");
	if (!extension_check(argv[1]))
		error_exit(NULL, "cub3d : File extension [.cub]");
	read_file(argv[1], &list);
	game_init(&game);
	file_info_parse(&game, list);
	ft_lstclear(&list, free);
	map_check(&game);
	decide_direction(&game);
	mlx_hook(game.win, DESTROY_NOTIFY, 1L << 17, &my_close, &game);
	mlx_hook(game.win, KEY_PRESS, 1L << 0, &deal_key, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	game_free(&game);
	return (0);
}
