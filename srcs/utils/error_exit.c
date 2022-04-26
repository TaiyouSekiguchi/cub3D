/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 09:59:53 by tsekiguc          #+#    #+#             */
/*   Updated: 2022/04/26 09:59:58 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	error_exit(char *cmd, char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (msg == NULL)
		perror(cmd);
	else
		ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
