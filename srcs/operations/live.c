/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 21:15:12 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/16 22:31:17 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_live(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int	player;

	player = get_argument(params->arena, carriage,
		(arg_code >> 6) & 3, 0);
	if (player > params->players_num || player < 1)
		return ;
	params->last_alive = player;
	params->live_count_in_period++;
	live_carriage(carriage, params->cycles_since_start);
	announce_player_alive(params->players, player);
}
