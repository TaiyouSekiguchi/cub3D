/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:51:52 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/04/25 22:51:53 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	map_check(t_game *game)
{
	int		**map;
	int		x;
	int		y;

	map = map_malloc(game);
	map_copy(game, map);
	y = 0;
	while (y < game->row)
	{
		x = 0;
		while (x < game->col)
		{
			if (map[y][x] == 0)
			{
				if (!close_check(game, map, x, y))
					error_exit(NULL,
						"cub3D : Map is not closed (or enconter space)");
				game->re_cnt = 20000;
			}
			x += 1;
		}
		y += 1;
	}
	map_free(game, map);
}
