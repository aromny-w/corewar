/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 23:22:30 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/15 23:26:46 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void op_fork(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int			arg;
	t_carriage	*copy;

	arg = get_argument(params->arena, carriage, T_DIR, 0);
	copy = duplicate_carriage(carriage, params->carriages_num,
		carriage->cur_position + (arg % IDX_MOD));
	insert_existing_carriage(&(params->carriages_list), copy);
	params->carriages_num++;
	(void)arg_code;
}
