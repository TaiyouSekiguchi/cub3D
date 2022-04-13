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

static void	map_malloc(t_game *game, int row, int col)
{
	int	i;
	int	j;

	game->world_map = (int **)malloc(sizeof(int *) * row);
	i = 0;
	while (i < row)
	{
		game->world_map[i] = (int *)malloc(sizeof(int) * col);
		j = 0;
		while (j < col)
		{
			game->world_map[i][j] = 0;
			j++;
		}
		i++;
	}
}

static void	map_parse(t_game *game, t_list *list, char *news, int col)
{
	t_list	*current;
	int		i;
	int		j;
	char	*line;
	char	c;

	current = list;
	i = 0;
	while (current != NULL)
	{
		line = current->content;
		if (is_empty_line(line))
			error_exit(NULL, "Empty line in map information.");
		j = 0;
		while (j < col)
		{
			c = line[j];
			if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
			{
				*news = c;
				game->player.pos_x = i;
				game->player.pos_y = j;
				game->world_map[i][j] = 0;
			}
			else if (c == ' ')
				game->world_map[i][j] = -1;
			else if (c == '0' || c == '1')
				game->world_map[i][j] = c - '0';
			else if (c == '\0')
				break ;
			else
			{
				printf("bad chara : %c %d\n", c, c);
				printf("i = %d j = %d\n", i, j);
				error_exit(NULL, "Forbidden character in map information.");
			}
			j++;
		}
		current = current->next;
		i++;
	}
}

void	make_map(t_game *game, t_list *list, char *news)
{
	int	row;
	int	col;

	get_row_and_col(list, &row, &col);
	map_malloc(game, row, col);
	map_parse(game, list, news, col);
	if (*news == '\0')
		error_exit(NULL, "No spawn character in map information.");
	game->row = row;
	game->col = col;
}
