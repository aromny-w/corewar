/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 21:15:12 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/10 00:40:51 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_live(t_carriage *carriage, t_game_params *params)
{
	int	player;

	player = -1 * get_registry(carriage, 1);
	params->last_alive = player;
	params->live_count_in_period++;
	live_carriage(carriage, params->cycles_since_start);
	announce_player_alive(params->players, player);
}
