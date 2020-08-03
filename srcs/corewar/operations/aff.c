/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 23:29:52 by bgilwood          #+#    #+#             */
/*   Updated: 2020/08/01 21:30:27 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_aff(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int	c;

	c = get_address_argument(params->arena, carriage, arg_code >> 6 & 3, 0);
	if (!(c > 0 && c <= REG_NUMBER))
		return ;
	c = get_registry(carriage, c);
	if (params->a_flag_on)
		ft_putchar(c);
}
