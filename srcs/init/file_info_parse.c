#include "cub3D.h"

static int		set_texture(t_game *game, char *path, int num)
{
	game->imgs[num].img = mlx_xpm_file_to_image(game->mlx, path,\
		&game->imgs[num].width, &game->imgs[num].height);
	if (game->imgs[num].img == NULL)
		error_exit("mlx", NULL);
	game->imgs[num].data = (int *)mlx_get_data_addr(game->imgs[num].img,\
		&game->imgs[num].bpp, &game->imgs[num].line_len, &game->imgs[num].endian);
	if (game->imgs[num].data == NULL)
		error_exit("mlx", NULL);
}

static void	set_color(int *color, const char *rgb)
{
	char	**split_rgb;
	int		red;
	int		green;
	int		blue;

	split_rgb = ft_split(rgb, ',');
	if (split_rgb == NULL)
		error_exit("malloc", NULL);
	if (ft_split_size(split_rgb) != 3)
		error_exit(NULL, "cub3D : Color format \"F(C) R,G,B\"");
	red = color_atoi(split_rgb[0]);
	green = color_atoi(split_rgb[1]);
	blue = color_atoi(split_rgb[2]);
	if (red > COLOR_MAX || green > COLOR_MAX || blue > COLOR_MAX)
		error_exit(NULL, "cub3D : Color range 0~255");
	*color = create_trgb(0, red, green, blue);
	ft_split_free(split_rgb);
}

static void	parse_check(t_game *game)
{
	if (game->imgs[0].img == NULL
		|| game->imgs[1].img == NULL
		|| game->imgs[2].img == NULL
		|| game->imgs[3].img == NULL
		|| game->floor == -1
		|| game->ceil == -1)
		error_exit(NULL, "cub3D : Lack of file information");
}

void	file_info_parse(t_game *game, t_list *list, char *news)
{
	t_list	*current;
	char	**split;

	current = list;
	while (current != NULL)
	{
		if (!is_empty_line(current->content))
		{
			split = ft_split(current->content, ' ');
			if (split == NULL)
				error_exit("malloc", NULL);
			if (ft_strcmp(split[0], "NO") == 0)
				set_texture(game, split[1], 0);
			else if (ft_strcmp(split[0], "SO") == 0)
				set_texture(game, split[1], 1);
			else if (ft_strcmp(split[0], "WE") == 0)
				set_texture(game, split[1], 2);
			else if (ft_strcmp(split[0], "EA") == 0)
				set_texture(game, split[1], 3);
			else if (ft_strcmp(split[0], "F") == 0)
				set_color(&game->floor, split[1]);
			else if (ft_strcmp(split[0], "C") == 0)
				set_color(&game->ceil, split[1]);
			else
			{
				ft_split_free(split);
				break ;
			}
			ft_split_free(split);
		}
		current = current->next;
	}
	parse_check(game);
	make_map(game, current, news);
}
