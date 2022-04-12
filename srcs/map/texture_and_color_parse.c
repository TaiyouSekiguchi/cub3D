#include "cub3D.h"

static void	do_color(int *color, const char *line)
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

static int		set_texture(t_game *game, char *path, int num)
{
	game->imgs[num].img = mlx_xpm_file_to_image(game->mlx, path, &game->imgs[num].width, &game->imgs[num].height);
	game->imgs[num].data = (int *)mlx_get_data_addr(game->imgs[num].img, &game->imgs[num].bpp, &game->imgs[num].line_len, &game->imgs[num].endian);
}

static int		is_empty_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
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

t_list	*texture_and_color_parse(t_game *game, t_list *list)
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
				do_color(&game->floor, split[1]);
			else if (ft_strcmp(split[0], "C") == 0)
				do_color(&game->ceil, split[1]);
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
	return (current);
}
