/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_and_ceilling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:58:59 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/04/25 23:59:00 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_floor_and_ceil(t_game *game)
{
	unsigned int	color;
	int				horizon;
	int				x;
	int				y;

	horizon = game->screen_height / 2;
	y = 0;
	while (y < horizon)
	{
		x = 0;
		while (x < game->screen_width)
		{
			color = game->floor;
			my_mlx_pixel_put(&game->img, x, y + horizon, color);
			color = game->ceil;
			my_mlx_pixel_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}
