/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 23:22:21 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/16 22:33:06 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_lldi(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int		args[3];
	int		value;

	args[0] = get_argument(params->arena, carriage, (arg_code >> 6) & 3, 0);
	args[1] = get_argument(params->arena, carriage, (arg_code >> 4) & 3, 0);
	args[2] = get_address_argument(params->arena, carriage, REG_CODE, 0);
	value = read_number(params->arena,
		carriage->cur_position + args[0] + args[1], REG_SIZE);
	save_registry(carriage, args[2], value);
	carriage->carry = value ? 0 : 1;
}
