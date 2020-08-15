/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:05:05 by malannys          #+#    #+#             */
/*   Updated: 2020/08/03 18:05:10 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

/*
** (2^8)^i
*/

int32_t		bin_to_num(uint8_t *val, size_t len)
{
	int32_t	sign;
	int32_t	res;
	size_t	i;

	i = 0;
	res = 0;
	sign = val[0] & 0x80 ? 1 : 0;
	while (i < len)
	{
		if (sign)
			val[len - i - 1] = ~val[len - i - 1];
		res += val[len - i - 1] << (8 * i);
		i++;
	}
	res += sign;
	return (sign ? -res : res);
}

int			rows_count(char **arr)
{
	int		i;

	i = 0;
	while (arr && *(arr + i))
		i++;
	return (i);
}
