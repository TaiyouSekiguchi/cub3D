/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:00:25 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/04/26 10:00:55 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	space_check(int **map, int x, int y)
{
	if (map[y][x - 1] == -2
		|| map[y + 1][x] == -2
		|| map[y][x + 1] == -2
		|| map[y - 1][x] == -2)
		return (1);
	return (0);
}

int	close_check(t_game *game, int **map, int x, int y)
{
	if (game->re_cnt == 0)
		error_exit(NULL, "cub3D : Map is too big");
	game->re_cnt--;
	if ((y == 0 || y == game->row - 1) || (x == 0 || x == game->col - 1))
		return (0);
	if (space_check(map, x, y))
		return (0);
	map[y][x] = -1;
	if (map[y][x - 1] == 0 && close_check(game, map, x - 1, y) == 0)
		return (0);
	if (map[y + 1][x] == 0 && close_check(game, map, x, y + 1) == 0)
		return (0);
	if (map[y][x + 1] == 0 && close_check(game, map, x + 1, y) == 0)
		return (0);
	if (map[y - 1][x] == 0 && close_check(game, map, x, y - 1) == 0)
		return (0);
	return (1);
}
