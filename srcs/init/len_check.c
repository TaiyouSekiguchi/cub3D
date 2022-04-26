/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:41:08 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/04/26 17:41:12 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	len_check(char **split)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (split[i] != NULL)
	{
		j = 0;
		while (split[i][j] != '\0')
		{
			j++;
			if (j >= INT_MAX)
				error_exit(NULL, "cub3D : File line is too long");
		}
		i++;
	}
}
