/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 23:22:45 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/16 20:50:22 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void op_lfork(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int			arg;
	t_carriage	*copy;

	arg = get_argument(params->arena, carriage, T_DIR, 1);
	copy = duplicate_carriage(carriage, params->carriages_num,
		carriage->cur_position + arg);
	insert_existing_carriage(&(params->carriages_list), copy);
	params->carriages_num++;
	(void)arg_code;
}
