#include "cub3D.h"

void	decide_direction(t_game *game, char news)
{
	double	direction;
	double	old_dir_x;
	double	old_plane_x;

	if(news != 'N')
	{
		if (news == 'E')
			direction = PI / 2;
		else if (news == 'S')
			direction = PI;
		else if (news == 'W')
			direction = PI * 3 / 2;
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-direction) - game->player.dir_y * sin(-direction);
		game->player.dir_y = old_dir_x * sin(-direction) + game->player.dir_y * cos(-direction);
		old_plane_x= game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-direction) - game->player.plane_y * sin(-direction);
		game->player.plane_y = old_plane_x* sin(-direction) + game->player.plane_y * cos(-direction);
	}
}

void	map_put(t_game *game)
{
	int	i;
	int	j;

	printf("   ");
	i = 0;
	while (i < game->col)
	{
		printf("%2d ", i);
		i++;
	}
	printf("\n");

	i = 0;
	while (i < game->row)
	{
		printf("%2d ", i);
		j = 0;
		while (j < game->col)
		{
			printf("%2d ", game->world_map[i][j]);
			j++;
		}
		printf("\n");
		i++;
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
	map_put(game);
}

int		main(int argc, char *argv[])
{
	t_list	*list;
	t_list	*map_list;
	t_game	game;
	char	news;

	if (argc != 2)
		error_exit(NULL, "Usage: ./cub3D file_name.cub");

	if (!extension_check(argv[1]))
		error_exit(NULL, "File extension is not (******.cub).");

	read_file(argv[1], &list);
	game_init(&game);
	map_list = texture_and_color_parse(&game, list);
	make_map(&game, map_list, &news);
	ft_lstclear(&list, free);

	file_read_result(&game);

	decide_direction(&game, news);
	mlx_hook(game.win, DESTROY_NOTIFY, 1L << 17, &my_close, &game);
	mlx_hook(game.win, KEY_PRESS, 1L << 0, &deal_key, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);

	//mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);

	mlx_loop(game.mlx);
	game_free(&game);
	return (0);
}
