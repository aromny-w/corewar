/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 23:30:21 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/16 22:33:36 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	write_color(int *color, int position, int size_bytes, int owner)
{
	int	i;

	i = -1;
	while (++i < size_bytes)
		color[get_new_coord(position + i)] = get_color(owner);
}

static int	check_reg_index(int *args, int *type)
{
	if ((type[0] == REG_CODE && !(args[0] > 0 && args[0] <= REG_NUMBER)) ||
	(type[1] == REG_CODE && !(args[1] > 0 && args[1] <= REG_NUMBER)) ||
	(type[2] == REG_CODE && !(args[2] > 0 && args[2] <= REG_NUMBER)))
		return (1);
	return (0);
}

void		op_sti(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int	args[3];
	int	type[3];
	int	i;

	i = -1;
	while (++i < 3)
	{
		if ((type[i] = arg_code >> (8 - (i + 1) * 2) & 3) == REG_CODE)
			args[i] = get_address_argument(params->arena, carriage, type[i], 0);
		else
			args[i] = get_argument(params->arena, carriage, type[i], 0);
	}
	if (check_reg_index(args, type))
		return ;
	if (type[0] == REG_CODE)
		args[0] = get_registry(carriage, args[0]);
	if (type[1] == REG_CODE)
		args[1] = get_registry(carriage, args[1]);
	if (type[2] == REG_CODE)
		args[2] = get_registry(carriage, args[2]);
	write_number(params->arena, carriage->cur_position +
				((args[1] + args[2]) % IDX_MOD), REG_SIZE, args[0]);
	if (params->v_flag_on)
		write_color(params->visu->color, carriage->cur_position +
		((args[1] + args[2]) % IDX_MOD), REG_SIZE, carriage->owner);
}
