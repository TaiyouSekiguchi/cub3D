#include "cub3D.h"

#define ERR_MSG "cub3D : Wrong format \"[identifier] [information]\""

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
	return (1);
}

static void	set_part(t_game *game, char **split)
{
	if (ft_split_size(split) != 2)
		error_exit(NULL, ERR_MSG);
	if (ft_strcmp(split[0], "NO") == 0)
		set_texture(game, split[1], NORTH);
	else if (ft_strcmp(split[0], "SO") == 0)
		set_texture(game, split[1], SOUTH);
	else if (ft_strcmp(split[0], "WE") == 0)
		set_texture(game, split[1], WEST);
	else if (ft_strcmp(split[0], "EA") == 0)
		set_texture(game, split[1], EAST);
	else if (ft_strcmp(split[0], "F") == 0)
		set_color(&game->floor, split[1]);
	else if (ft_strcmp(split[0], "C") == 0)
		set_color(&game->ceil, split[1]);
}

void	file_info_parse(t_game *game, t_list *list)
{
	char	**split;

	while (list != NULL)
	{
		if (!is_empty_line(list->content))
		{
			split = ft_split(list->content, ' ');
			if (split == NULL)
				error_exit("malloc", NULL);
			if (is_info(split[0]))
				set_part(game, split);
			else if (is_map(split))
			{
				ft_split_free(split);
				break ;
			}
			else
				error_exit(NULL, "cub3D : Unknown information");
			ft_split_free(split);
		}
		list = list->next;
	}
	parse_check(game);
	make_map(game, list);
}
