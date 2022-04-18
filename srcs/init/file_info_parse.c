#include "cub3D.h"

static int	set_texture(t_game *game, char *path, int num)
{
	if (path == NULL)
		error_exit(NULL, "cub3D : Texture format \"NO(SO, WE, EA) file_path\"");
	if (game->imgs[num].img != NULL)
		error_exit(NULL, "cub3D : Texture path is already set");
	game->imgs[num].img = mlx_xpm_file_to_image(game->mlx, path,\
		&game->imgs[num].width, &game->imgs[num].height);
	if (game->imgs[num].img == NULL)
		error_exit("mlx", NULL);
	game->imgs[num].data = (int *)mlx_get_data_addr(game->imgs[num].img,\
		&game->imgs[num].bpp, &game->imgs[num].line_len, &game->imgs[num].endian);
	if (game->imgs[num].data == NULL)
		error_exit("mlx", NULL);
}

static int	comma_count(char *rgb)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (rgb[i] != '\0')
	{
		if (rgb[i] == ',')
			count++;
		i++;
	}
	return (count);
}

static void	set_color(int *color, char *rgb)
{
	char	**split_rgb;
	int		red;
	int		green;
	int		blue;

	if (rgb == NULL || comma_count(rgb) != 2)
		error_exit(NULL, "cub3D : Color format \"F(C) R,G,B\"");
	if (*color != -1)
		error_exit(NULL, "cub3D : Color is already set");
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

static int	is_info(char *identifier)
{
	if (ft_strcmp(identifier, "NO") == 0
		|| ft_strcmp(identifier, "SO") == 0
		|| ft_strcmp(identifier, "WE") == 0
		|| ft_strcmp(identifier, "EA") == 0
		|| ft_strcmp(identifier, "F") == 0
		|| ft_strcmp(identifier, "C") == 0)
		return (1);
	return (0);
}

static int	is_permitted_char_in_map(char c)
{
	if (c == '0'
		|| c == '1'
		|| c == 'N'
		|| c == 'E'
		|| c == 'W'
		|| c == 'S'
		|| c == ' ')
		return (1);
	return (0);
}

static int	is_map(char **split)
{
	int	i;
	int	j;

	i = 0;
	while (split[i] != NULL)
	{
		j = 0;
		while (split[i][j] != '\0')
		{
			if (!is_permitted_char_in_map(split[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return(1);
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
			if (is_info(split[0]))
			{
				if (ft_split_size(split) != 2)
					error_exit(NULL, "cub3D : Wrong format \"[identifier] [information]\"");
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
			}
			else if (is_map(split))
			{
				ft_split_free(split);
				break ;
			}
			else
				error_exit(NULL, "cub3D : Unknown information");
			ft_split_free(split);
		}
		current = current->next;
	}
	parse_check(game);
	make_map(game, current, news);
}
