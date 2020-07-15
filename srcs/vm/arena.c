/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 00:59:52 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/15 22:14:53 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "vm.h"

void	*arena_init(void)
{
	void	*mem;

	mem = ft_memalloc(MEM_SIZE);
	if (!mem)
		error("Memory error, the virtual machine is stopping now.");
	return (mem);
}

int		get_new_coord(int raw_coord)
{
	raw_coord %= MEM_SIZE;
	if (raw_coord < 0)
		raw_coord += MEM_SIZE;
	return (raw_coord);
}

int		arena_read_byte(char *arena, int cur_position)
{
	char	ans;

	cur_position = get_new_coord(cur_position);
	ans = arena[cur_position];
	return (ans);
}

int		read_number(char *arena, int position, int size_bytes)
{
	int				result;
	int				sign;
	int				i;
	unsigned char	*byte_code;

	position = get_new_coord(position);
	byte_code = (unsigned char *)arena + position;
	sign = byte_code[0] & 128;
	i = 0;
	result = 0;
	while (size_bytes)
	{
		size_bytes--;
		if (sign)
			result += byte_code[size_bytes] ^ 255 << i;
		else
			result += byte_code[size_bytes] & 255 << i;
		i++;
	}
	return (sign ? ~result : result);
}

void	write_number(char *arena, int position, int size_bytes, int number)
{
	char	byte[4];

	position = get_new_coord(position);
	if (size_bytes > 4)
		size_bytes = 4;
	byte[0] = number >> 24;
	byte[1] = number >> 16;
	byte[2] = number >> 8;
	byte[3] = number;
	ft_memcpy(arena + position, byte + 4 - size_bytes, size_bytes);
}
