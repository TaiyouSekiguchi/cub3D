#include "cub3D.h"

void	file_init(t_file *file)
{
	file->screenWidth = 0;
	file->screenHeight = 0;
	file->floor = 0;
	file->ceil = 0;
	file->north = NULL;
	file->south = NULL;
	file->east = NULL;
	file->west = NULL;
	file->sprite = NULL;
	file->map = NULL;
}

void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->file.screenWidth, game->file.screenHeight, "Hello, Raycaster");
}

void	player_init(t_game *game)
{
	game->player.posX = 0;
	game->player.posY = 0;
	game->player.dirX = -1;
	game->player.dirY = 0;
	game->player.planeX = 0;
	game->player.planeY = 0.66;
}

void	img_init(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, game->file.screenWidth, game->file.screenHeight);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_len, &game->img.endian);
}

void	do_R(t_file *file, const char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] >= '0' && line[i] <= '9')
	{
		while (line[i] >= '0' && line[i] <= '9')
		{
			file->screenWidth = file->screenWidth * 10 + (line[i] - '0');
			i++;
		}
	}
	else
		printf("Error\n");
	while (line[i] == ' ')
		i++;
	if (line[i] >= '0' && line[i] <= '9')
	{
		while (line[i] >= '0' && line[i] <= '9')
		{
			file->screenHeight = file->screenHeight * 10 + (line[i] - '0');
			i++;
		}
	}
	else
		printf("Error\n");
}

void	do_pass(char **str, const char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	*str = my_strdup(&line[i], '\0');
	if (*str == NULL)
		printf("Error\n");
}

void	do_color(int *color, const char *line)
{
	int		red;
	int		green;
	int		blue;
	int		i;

	red = 0;
	green = 0;
	blue =0;
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] >= '0' && line[i] <= '9')
	{
		while (line[i] >= '0' && line[i] <= '9')
		{
			red = red * 10 + (line[i] - '0');
			i++;
		}
	}
	i++;
	while (line[i] == ' ')
		i++;
	if (line[i] >= '0' && line[i] <= '9')
	{
		while (line[i] >= '0' && line[i] <= '9')
		{
			green = green * 10 + (line[i] - '0');
			i++;
		}
	}
	i++;
	while (line[i] == ' ')
		i++;
	if (line[i] >= '0' && line[i] <= '9')
	{
		while (line[i] >= '0' && line[i] <= '9')
		{
			blue = blue * 10 + (line[i] - '0');
			i++;
		}
	}
	*color = create_trgb(0, red, green, blue);
}


void	do_map(char **map,char *line)
{
	if (*map == NULL)
	{
		*map = my_strdup(line, '\0');
		*map = my_strjoin(*map, "\n", '\0');
	}
	else
	{
		*map = my_strjoin(*map, line, '\0');
		*map = my_strjoin(*map, "\n", '\0');
	}
	if (*map == NULL)
		printf("Error\n");
}

void	do_identifier(char *line, t_file *file)
{
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R')
		do_R(file, &line[i + 1]);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		do_pass(&file->north, &line[i + 2]);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		do_pass(&file->south, &line[i + 2]);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		do_pass(&file->west, &line[i + 2]);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		do_pass(&file->east, &line[i + 2]);
	else if (line[i] == 'S')
		do_pass(&file->sprite, &line[i + 1]);
	else if (line[i] == 'F')
		do_color(&file->floor, &line[i + 1]);
	else if (line[i] == 'C')
		do_color(&file->ceil, &line[i + 1]);
	else if (line[i] == '1')
		do_map(&file->map, line);
}

void	map_count(t_file *file, t_counter *map_cnt)
{
	int		char_cnt;
	int		i;

	map_cnt->map_max_len = 0;
	map_cnt->map_line_cnt = 0;
	map_cnt->sprite_cnt = 0;
	char_cnt = 0;
	i = 0;
	while (file->map[i] != '\0')
	{
		if (file->map[i] == '\n')
		{
			if (map_cnt->map_max_len < char_cnt)
				map_cnt->map_max_len = char_cnt;
			char_cnt = 0;
			map_cnt->map_line_cnt++;
		}
		else if (file->map[i] == '2')
			map_cnt->sprite_cnt++;
		else
			char_cnt++;
		i++;
	}
}

void	map_alloc(int ***worldMap, t_counter *map_cnt)
{
	int		i;
	int		j;

	*worldMap = (int **)malloc(sizeof(int *) * map_cnt->map_line_cnt);
	i = 0;
	while (i < map_cnt->map_line_cnt)
	{
		(*worldMap)[i] = (int *)malloc(sizeof(int) * map_cnt->map_max_len);
		j = 0;
		while (j < map_cnt->map_max_len)
		{
			(*worldMap)[i][j] = -1;
			j++;
		}
		i++;
	}
}

void	my_error(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int		extension_check(char *file_path)
{
	size_t	len;

	printf("file_path : %s\n", file_path);
	len = ft_strlen(file_path);
	if (len <= 4)
		return (0);
	if (file_path[len - 4] == '.'
		&& file_path[len - 3] == 'c'
		&& file_path[len - 2] == 'u'
		&& file_path[len - 1] == 'b')
		return (1);
	return (0);
}

int		read_file(char *file_name, t_file *file)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	while (get_next_line(fd, &line) > 0)
	{
		do_identifier(line, file);
		free(line);
	}
	do_identifier(line, file);
	free(line);
	return (EXIT_SUCCESS);
}

void map_create(t_game *game, char *news)
{
	int i;
	int j;
	int s;
	int t;

	t = 0;
	s = 0;
	i = 0;
	while (i < game->map_cnt.map_line_cnt)
	{
		j = 0;
		while (j < game->map_cnt.map_max_len)
		{
			if (game->file.map[t] != ' ')
			{
				if (game->file.map[t] == 'N'
					|| game->file.map[t] == 'E'
					|| game->file.map[t] == 'W' 
					|| game->file.map[t] == 'S')
				{
					*news = game->file.map[t];
					game->player.posX = j;
					game->player.posY = i;
					game->worldMap[i][j] = 0;
				}
				else if (game->file.map[t] == '2')
				{
					game->sprite[s].x = j;
					game->sprite[s].y = i;
					game->sprite[s].texture = 8;
					game->worldMap[i][j] = 0;
					s++;
				}
				else
					game->worldMap[i][j] = game->file.map[t] - '0';
			}
			j++;
			t++;
			if (game->file.map[t] == '\n')
			{
				t++;
				break;
			}
		}
		i++;
	}
}

void	decide_direction(t_game *game, char news)
{
	double	direction;

	if(news != 'N')
	{
		if (news == 'E')
			direction = PI / 2;
		else if (news == 'S')
			direction = PI;
		else if (news == 'W')
			direction = PI * 3 / 2;
		double oldDirX = game->player.dirX;
		game->player.dirX = game->player.dirX * cos(-direction) - game->player.dirY * sin(-direction);
		game->player.dirY = oldDirX * sin(-direction) + game->player.dirY * cos(-direction);
		double oldPlaneX = game->player.planeX;
		game->player.planeX = game->player.planeX * cos(-direction) - game->player.planeY * sin(-direction);
		game->player.planeY = oldPlaneX * sin(-direction) + game->player.planeY * cos(-direction);
	}
}

int		set_texture(t_game *game)
{
	game->imgs[0].img = mlx_xpm_file_to_image(game->mlx, "./texture/eagle.xpm", &game->imgs[0].width, &game->imgs[0].height);
	game->imgs[0].data = (int *)mlx_get_data_addr(game->imgs[0].img, &game->imgs[0].bpp, &game->imgs[0].line_len, &game->imgs[0].endian);
	game->imgs[1].img = mlx_xpm_file_to_image(game->mlx, "./texture/redbrick.xpm", &game->imgs[1].width, &game->imgs[1].height);
	game->imgs[1].data = (int *)mlx_get_data_addr(game->imgs[1].img, &game->imgs[1].bpp, &game->imgs[1].line_len, &game->imgs[1].endian);
	game->imgs[2].img = mlx_xpm_file_to_image(game->mlx, "./texture/purplestone.xpm", &game->imgs[2].width, &game->imgs[2].height);
	game->imgs[2].data = (int *)mlx_get_data_addr(game->imgs[2].img, &game->imgs[2].bpp, &game->imgs[2].line_len, &game->imgs[2].endian);
	game->imgs[3].img = mlx_xpm_file_to_image(game->mlx, "./texture/greystone.xpm", &game->imgs[3].width, &game->imgs[3].height);
	game->imgs[3].data = (int *)mlx_get_data_addr(game->imgs[3].img, &game->imgs[3].bpp, &game->imgs[3].line_len, &game->imgs[3].endian);
	game->imgs[4].img = mlx_xpm_file_to_image(game->mlx, "./texture/bluestone.xpm", &game->imgs[4].width, &game->imgs[4].height);
	game->imgs[4].data = (int *)mlx_get_data_addr(game->imgs[4].img, &game->imgs[4].bpp, &game->imgs[4].line_len, &game->imgs[4].endian);
	game->imgs[5].img = mlx_xpm_file_to_image(game->mlx, "./texture/mossy.xpm", &game->imgs[5].width, &game->imgs[5].height);
	game->imgs[5].data = (int *)mlx_get_data_addr(game->imgs[5].img, &game->imgs[5].bpp, &game->imgs[5].line_len, &game->imgs[5].endian);
	game->imgs[6].img = mlx_xpm_file_to_image(game->mlx, "./texture/wood.xpm", &game->imgs[6].width, &game->imgs[6].height);
	game->imgs[6].data = (int *)mlx_get_data_addr(game->imgs[6].img, &game->imgs[6].bpp, &game->imgs[6].line_len, &game->imgs[6].endian);
	game->imgs[7].img = mlx_xpm_file_to_image(game->mlx, "./texture/colorstone.xpm", &game->imgs[7].width, &game->imgs[7].height);
	game->imgs[7].data = (int *)mlx_get_data_addr(game->imgs[7].img, &game->imgs[7].bpp, &game->imgs[7].line_len, &game->imgs[7].endian);
	game->imgs[8].img = mlx_xpm_file_to_image(game->mlx, "./texture/barrel.xpm", &game->imgs[8].width, &game->imgs[8].height);
	game->imgs[8].data = (int *)mlx_get_data_addr(game->imgs[8].img, &game->imgs[8].bpp, &game->imgs[8].line_len, &game->imgs[8].endian);
	game->imgs[9].img = mlx_xpm_file_to_image(game->mlx, "./texture/pillar.xpm", &game->imgs[9].width, &game->imgs[9].height);
	game->imgs[9].data = (int *)mlx_get_data_addr(game->imgs[9].img, &game->imgs[9].bpp, &game->imgs[9].line_len, &game->imgs[9].endian);
	game->imgs[10].img = mlx_xpm_file_to_image(game->mlx, "./texture/greenlight.xpm", &game->imgs[10].width, &game->imgs[10].height);
	game->imgs[10].data = (int *)mlx_get_data_addr(game->imgs[10].img, &game->imgs[10].bpp, &game->imgs[10].line_len, &game->imgs[10].endian);
	return (1);
}


int		main(int argc, char *argv[])
{
	t_game	game;
	char	news;

	if (argc != 2)
		my_error("Usage: ./cub3D file_name.cub");
	if (!extension_check(argv[1]))
		my_error("File extension is not (******.cub).");

	file_init(&game.file);
	if (read_file(argv[1], &game.file))
		my_error("File open failed.");

	map_count(&game.file, &game.map_cnt);
	map_alloc(&game.worldMap, &game.map_cnt);
	player_init(&game);
	game.sprite = (t_Sprite *)malloc(sizeof(t_Sprite) * game.map_cnt.sprite_cnt);

	map_create(&game, &news);
	window_init(&game);
	decide_direction(&game, news);

	img_init(&game);
	set_texture(&game);

	mlx_hook(game.win, DESTROY_NOTIFY, 1L << 17, &my_close, &game);
	mlx_hook(game.win, KEY_PRESS, 1L << 0, &deal_key, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
}
