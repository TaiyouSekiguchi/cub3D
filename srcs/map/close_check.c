#include "cub3D.h"

static void	map_put(t_game *game, int **map, int x, int y)
{
	int	i;
	int j;

	printf("***********************************************\n");
	i = 0;
	while (i < game->row)
	{
		j = 0;
		while (j < game->col)
		{
			printf(" %2d", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("***********************************************\n");
	printf("row : %d   col : %d\n", game->row, game->col);
	printf("x   : %d   y   : %d\n", x, y);
}

int		close_check(t_game *game, int **map, int x, int y)
{
	//map_put(game, map, x, y);
	if ((x == 0 || x == game->row - 1) || (y == 0 || y == game->col - 1))
		return (0);
	else
	{
		map[x][y] = -1;
		if (map[x][y - 1] == 0)
		{
			if (close_check(game, map, x, y - 1) == 0)
				return (0);
		}
		if (map[x + 1][y] == 0)
		{
			if (close_check(game, map, x + 1, y) == 0)
				return (0);
		}
		if (map[x][y + 1] == 0)
		{
			if (close_check(game, map, x, y + 1) == 0)
				return (0);
		}
		if (map[x - 1][y] == 0)
		{
			if (close_check(game, map, x - 1, y) == 0)
				return (0);
		}
		return (1);
	}
}
