/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 21:15:12 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/19 20:47:49 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_live(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int	player;

	player = -get_argument(params->arena, carriage, DIR_CODE, 0);
	live_carriage(carriage, params->cycles_since_start);
	params->live_count_in_period++;
	if (player > params->players_num || player < 1)
		return ;
	params->last_alive = player;
	announce_player_alive(params->players, player);
	(void)arg_code;
}
