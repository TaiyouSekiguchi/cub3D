/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:51:56 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/04/25 22:51:57 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

u_int8_t	get_t(unsigned int trgb)
{
	return ((trgb & (0xFF << 24)) >> 24);
}

u_int8_t	get_r(unsigned int trgb)
{
	return ((trgb & (0xFF << 16)) >> 16);
}

u_int8_t	get_g(unsigned int trgb)
{
	return ((trgb & (0xFF << 8)) >> 8);
}

u_int8_t	get_b(unsigned int trgb)
{
	return (trgb & 0xFF);
}
