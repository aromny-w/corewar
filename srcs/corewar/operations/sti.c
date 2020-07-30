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

void	op_sti(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int		args[3];

	args[0] = get_argument(params->arena, carriage, (arg_code >> 6) & 3, 0);
	args[1] = get_argument(params->arena, carriage, (arg_code >> 4) & 3, 0);
	args[2] = get_argument(params->arena, carriage, (arg_code >> 2) & 3, 0);
	write_number(params->arena, carriage->cur_position +
				((args[1] + args[2]) % IDX_MOD), REG_SIZE, args[0]);
}
