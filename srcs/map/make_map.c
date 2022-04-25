#include "cub3D.h"

static void	get_row_and_col(t_list *list, int *row, int *col)
{
	t_list	*current;
	int		len;

	*row = 0;
	*col = 0;
	current = list;
	while (current != NULL)
	{
		*row += 1;
		len = ft_strlen(current->content);
		if (*col < len)
			*col = len;
		current = current->next;
	}
}

static int	**map_malloc(int row, int col)
{
	int	**map;
	int	i;
	int	j;

	map = (int **)malloc(sizeof(int *) * row);
	if (map == NULL)
		error_exit("malloc", NULL);
	i = 0;
	while (i < row)
	{
		map[i] = (int *)malloc(sizeof(int) * col);
		if (map[i] == NULL)
			error_exit("malloc", NULL);
		j = 0;
		while (j < col)
		{
			map[i][j] = -2;
			j++;
		}
		i++;
	}
	return (map);
}

static void	set_world_map(t_game *game, char c, int i, int j)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
	{
		if (game->news != '\0')
			error_exit(NULL, "cub3D : Multiple spawn character");
		game->news = c;
		game->player.pos_x = i + 0.5;
		game->player.pos_y = j + 0.5;
		game->world_map[i][j] = 0;
	}
	else if (c == ' ')
		game->world_map[i][j] = -2;
	else if (c == '0' || c == '1')
		game->world_map[i][j] = c - '0';
	else
		error_exit(NULL, "cub3D : Forbidden character in map");
}

static void	map_parse(t_game *game, t_list *list)
{
	t_list	*current;
	char	*line;
	int		i;
	int		j;

	current = list;
	i = 0;
	while (current != NULL)
	{
		line = current->content;
		if (is_empty_line(line))
			error_exit(NULL, "cub3D : Empty line in map.");
		j = 0;
		while (j < game->col && line[j] != '\0')
		{
			set_world_map(game, line[j], i, j);
			j++;
		}
		current = current->next;
		i++;
	}
}

void	make_map(t_game *game, t_list *list)
{
	get_row_and_col(list, &game->row, &game->col);
	game->world_map = map_malloc(game->row, game->col);
	map_parse(game, list);
	if (game->news == '\0')
		error_exit(NULL, "cub3D : No spawn character.");
}
