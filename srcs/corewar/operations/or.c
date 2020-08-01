/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 22:32:30 by bgilwood          #+#    #+#             */
/*   Updated: 2020/08/01 22:43:24 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_or(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int		args[3];
	int		arg_type;
	int		res;
	int		fill_reg_arg_result;

	fill_reg_arg_result = 1;
	arg_type = (arg_code >> 6) & 3;
	if (arg_type == REG_CODE)
		fill_reg_arg_result = fill_reg_arg(args, params->arena, carriage);
	else
		args[0] = get_argument(params->arena, carriage, arg_type, 0);
	arg_type = (arg_code >> 4) & 3;
	if (arg_type == REG_CODE)
		fill_reg_arg_result = fill_reg_arg(args + 1, params->arena, carriage);
	else
		args[1] = get_argument(params->arena, carriage, arg_type, 0);
	args[2] = get_address_argument(params->arena, carriage, REG_CODE, 0);
	if (!fill_reg_arg_result)
	{
		carriage->carry = 0;
		return ;
	}
	res = args[0] | args[1];
	save_registry(carriage, args[2], res);
	carriage->carry = res ? 0 : 1;
}
