/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 22:28:38 by bgilwood          #+#    #+#             */
/*   Updated: 2020/08/01 22:42:54 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_and(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int	args[3];
	int	type[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		if ((type[i] = arg_code >> (8 - (i + 1) * 2) & 3) == REG_CODE)
			args[i] = get_address_argument(params->arena, carriage, type[i], 0);
		else
			args[i] = get_argument(params->arena, carriage, type[i], 0);
		i++;
	}
	if ((type[0] == REG_CODE && !(args[0] > 0 && args[0] <= REG_NUMBER)) ||
	(type[1] == REG_CODE && !(args[1] > 0 && args[1] <= REG_NUMBER)) ||
	(type[2] == REG_CODE && !(args[2] > 0 && args[2] <= REG_NUMBER)))
		return ;
	if (type[0] == REG_CODE)
		args[0] = get_registry(carriage, args[0]);
	if (type[1] == REG_CODE)
		args[1] = get_registry(carriage, args[1]);
	save_registry(carriage, args[2], args[0] & args[1]);
	carriage->carry = args[0] & args[1] ? 0 : 1;
}
/*
void			op_and(t_carriage *carriage, t_game_params *params,
																int arg_code)
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
	res = args[0] & args[1];
	save_registry(carriage, args[2], res);
	carriage->carry = res ? 0 : 1;
}*/
