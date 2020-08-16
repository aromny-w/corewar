/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 00:19:44 by aromny-w          #+#    #+#             */
/*   Updated: 2018/12/16 18:32:39 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	n;
	int		sign;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	n = 0;
	while (ft_isdigit(*str))
	{
		if (n != n * 10 / 10)
			return ((int)(sign == 1 ? LONG_MAX : LONG_MIN));
		n = 10 * n + (*str++ - '0');
	}
	return (n * sign);
}
