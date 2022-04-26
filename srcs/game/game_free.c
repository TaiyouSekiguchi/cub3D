/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:59:19 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/04/25 23:59:20 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	destroy_map(int **map, int row)
{
	int	i;

	i = 0;
	while (i < row)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	destroy_imgs(void *mlx, t_img *imgs)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(mlx, imgs[i].img);
		i++;
	}
}

void	game_free(t_game *game)
{
	destroy_map(game->world_map, game->row);
	destroy_imgs(game->mlx, game->imgs);
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}
