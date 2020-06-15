/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 00:59:52 by bgilwood          #+#    #+#             */
/*   Updated: 2020/06/14 22:37:24 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "vm.h"

void	*arena_init()
{
    void	*mem;

    mem = ft_memalloc(MEM_SIZE);
	if (!mem)
		;//error exit
    return (mem);
}

int		get_new_coord(int raw_coord)
{
	raw_coord %= MEM_SIZE;
	if (raw_coord < 0)
		raw_coord += MEM_SIZE;
	return (raw_coord);
}

int		arena_read(char *arena, int cur_position)
{
	char	ans;

	ans = arena[cur_position];
	return(ans);
}

long int	read_number(char *arena, int position, int size_bytes)
{
	// read bytes and this locations and transform into number (remember endianness!)
}

void		write_number(char *arena, int position, int size_bytes, int number)
{

}