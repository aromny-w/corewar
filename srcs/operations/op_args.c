/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 20:03:14 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/14 21:50:46 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_argument(char *arena, t_carriage *carriage, int arg_type, int l_op)
{
	int		temp;
	int		num;
	int		position;
	int		dir_size;

	dir_size = g_op_tab[carriage->code_op - 1].idx ? IND_SIZE : DIR_SIZE;
	position = carriage->cur_position + carriage->bytes_next_op;
	if (arg_type == DIR_CODE)
		num = read_number(arena, position, dir_size);
	if (arg_type == IND_CODE)
	{
		temp = read_number(arena, position, IND_SIZE);
		temp = l_op ? temp : temp % IDX_MOD;
		num = read_number(arena, get_new_coord(carriage->cur_position + temp),
			DIR_SIZE);
	}
	if (arg_type == REG_CODE)
		num = get_registry(carriage, read_number(arena, position, REG_SIZE));
	if (arg_type == DIR_CODE)
		carriage->bytes_next_op += dir_size;
	else
		carriage->bytes_next_op += (arg_type == IND_CODE ? IND_SIZE : REG_SIZE);
	return (num);
}
