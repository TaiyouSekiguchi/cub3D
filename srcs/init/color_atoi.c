/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:00:08 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/04/26 00:00:09 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_part(unsigned int *num, int *minus, int *i)
{
	*num = 0;
	*minus = 0;
	*i = 0;
}

static void	loop_part(char *str, int *i, unsigned int *num, int minus)
{
	while (ft_isdigit(str[*i]))
	{
		if (!ft_int_check(*num, str[*i] - '0', minus))
			error_exit(NULL, "cub3D : Color range 0~255");
		*num = *num * 10 + (str[*i] - '0');
		*i += 1;
	}
}

int	color_atoi(char *str)
{
	unsigned int	num;
	int				minus;
	int				i;

	init_part(&num, &minus, &i);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus = 1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		error_exit(NULL, "cub3D : Forbidden character in color");
	loop_part(str, &i, &num, minus);
	if (str[i] != '\0' && !ft_isspace(str[i]))
		error_exit(NULL, "cub3D : Forbidden character in color");
	if (minus != 0)
		error_exit(NULL, "cub3D : Color range 0~255");
	return (num);
}
