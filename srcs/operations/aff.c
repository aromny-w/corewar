/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 23:29:52 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/16 22:31:50 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_aff(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int	c;

	c = get_argument(params->arena, carriage, (arg_code >> 6) & 3, 0);
	ft_putchar((char)c);
}
