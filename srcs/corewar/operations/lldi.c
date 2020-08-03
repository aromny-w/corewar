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

#include "corewar.h"

void	op_lldi(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int	args[3];
	int	type[3];
	int	value;
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
	value = read_number(params->arena,
		carriage->cur_position + args[0] + args[1], REG_SIZE);
	save_registry(carriage, args[2], value);
	carriage->carry = value ? 0 : 1;
}
