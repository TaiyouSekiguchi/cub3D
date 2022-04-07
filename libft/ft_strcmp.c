/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 20:06:27 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/12/31 20:18:04 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*ucs1;
	unsigned char	*ucs2;
	size_t			i;

	ucs1 = (unsigned char *)s1;
	ucs2 = (unsigned char *)s2;
	i = 0;
	while (ucs1[i] == ucs2[i])
	{
		if (ucs1[i] == '\0')
			return (0);
		i++;
	}
	return (ucs1[i] - ucs2[i]);
}
