/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 22:33:00 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/16 22:32:59 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_xor(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int		args[3];
	int		arg_type;
	int		res;

	arg_type = (arg_code >> 6) & 3;
	args[0] = get_argument(params->arena, carriage, arg_type, 0);
	arg_type = (arg_code >> 4) & 3;
	args[1] = get_argument(params->arena, carriage, arg_type, 0);
	args[2] = get_address_argument(params->arena, carriage, REG_CODE, 0);
	res = args[0] ^ args[1];
	save_registry(carriage, args[2], res);
	carriage->carry = res ? 0 : 1;
}
