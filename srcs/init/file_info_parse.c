#include "cub3D.h"

static size_t split_size(char **split)
{
	int		i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

static int	color_atoi(char *str)
{
	unsigned int	num;
	int				minus;
	int				i;

	minus = 0;
	num = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus = 1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		error_exit(NULL, "Floor or Ceilling color : Non digit character exist.");
	while (ft_isdigit(str[i]))
	{
		if (!ft_int_check(num, str[i] - '0', minus))
			error_exit(NULL, "Floor or Ceilling color : Num is not INT.");
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' && !ft_isspace(str[i]))
		error_exit(NULL, "Floor or Ceilling color : Non digit character exist.");
	if (minus == 0)
		return (num);
	else
		error_exit(NULL, "Floor or Ceilling color : Negative num exist.");
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
	if (split_size(split_rgb) != 3)
		error_exit(NULL, "Floor or Ceilling : \"F(C) R,G,B\"");
	red = color_atoi(split_rgb[0]);
	green = color_atoi(split_rgb[1]);
	blue = color_atoi(split_rgb[2]);
	if (red > 255 || green > 255 || blue > 255)
		error_exit(NULL, "Floor or Ceilling color : larger than 255.");
	*color = create_trgb(0, red, green, blue);
}

static int		set_texture(t_game *game, char *path, int num)
{
	game->imgs[num].img = mlx_xpm_file_to_image(game->mlx, path, &game->imgs[num].width, &game->imgs[num].height);
	if (game->imgs[num].img == NULL)
		error_exit("mlx", NULL);
	game->imgs[num].data = (int *)mlx_get_data_addr(game->imgs[num].img, &game->imgs[num].bpp, &game->imgs[num].line_len, &game->imgs[num].endian);
	if (game->imgs[num].data == NULL)
		error_exit("mlx", NULL);
}

static int		parse_check(t_game *game)
{
	if (game->imgs[0].img == NULL
		|| game->imgs[1].img == NULL
		|| game->imgs[2].img == NULL
		|| game->imgs[3].img == NULL
		|| game->floor == -1
		|| game->ceil == -1)
		return (1);
	return (0);
}

void	split_free(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
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
				split_free(split);
				break ;
			}
			split_free(split);
		}
		current = current->next;
	}
	if (parse_check(game))
		error_exit(NULL, "File information is not enough.");
	make_map(game, current, news);
}
