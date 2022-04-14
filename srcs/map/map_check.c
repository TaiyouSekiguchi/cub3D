#include "cub3D.h"

static int	**map_malloc(t_game *game)
{
	int		**map;
	int		i;

	map = (int **)malloc(sizeof(int *) * game->row);
	if (map == NULL)
		error_exit("malloc", NULL);
	i = 0;
	while (i < game->row)
	{
		map[i] = (int *)malloc(sizeof(int) * game->col);
		if (map[i] == NULL)
			error_exit("malloc", NULL);
		i++;
	}
	return (map);
}

static void	map_copy(t_game *game, int **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->row)
	{
		j = 0;
		while (j < game->col)
		{
			map[i][j] = game->world_map[i][j];
			j++;
		}
		i++;
	}
}

static	void map_put(t_game *game, int **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->row)
	{
		j = 0;
		while (j < game->col)
		{
			printf(" %d ", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

static void	map_free(t_game *game, int **map)
{
	int		i;

	i = 0;
	while (i < game->row)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

int		map_check(t_game *game)
{
	int	**map;

	map = map_malloc(game);
	map_copy(game, map);
	if (!close_check(game, map, game->player.pos_x, game->player.pos_y))
		error_exit(NULL, "cub3D : Map is not closed (or enconter space)");
	map_free(game, map);
}
