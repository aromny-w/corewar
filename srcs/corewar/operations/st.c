/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 21:42:07 by bgilwood          #+#    #+#             */
/*   Updated: 2020/08/01 20:53:14 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_st(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int		args[2];
	int		arg2_type;

	arg2_type = (arg_code >> 4) & 3;
	args[0] = get_address_argument(params->arena, carriage, REG_CODE, 0);
	args[1] = get_address_argument(params->arena, carriage, arg2_type, 0);
	if (!(args[0] > 0 && args[0] <= REG_NUMBER) || (arg2_type == REG_CODE &&
	!(args[1] > 0 && args[1] <= REG_NUMBER)))
		return ;
	args[0] = get_registry(carriage, args[0]);
	if (arg2_type == REG_CODE)
		save_registry(carriage, args[1], args[0]);
	else
	{
		write_number(params->arena, carriage->cur_position + args[1], REG_SIZE,
				args[0]);
	}
}
