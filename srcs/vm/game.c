/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 00:06:41 by bgilwood          #+#    #+#             */
/*   Updated: 2020/06/16 00:44:25 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	check_carriages(t_car_list_elem **carriages, t_game_params *params)
{
	t_car_list_elem	*elem;
	t_car_list_elem	*next_elem;

	elem = *carriages;
	if (!elem || !elem->next)
		; // declare winner
	while (elem)
	{
		next_elem = elem->next;
		if (params->cycles_since_start - elem->content->last_live > params->cycles_to_die)
		{
			delete_carriage_elem(carriages, elem->content->id);
		}
		elem = next_elem;
	}
	if (params->live_count_in_period > NBR_LIVE || params->checks_count > MAX_CHECKS)
	{
		params->cycles_to_die -= CYCLE_DELTA;
		params->checks_count = 0;
	}
	params->live_count_in_period = 0;
	params->cycles_since_last_check = 0;
}

void	play_cycle(t_car_list_elem **carriages, t_game_params *params)
{
	t_car_list_elem	*carriage;

	if (params->cycles_since_last_check > CYCLE_TO_DIE)
		check_carriages(carriages, params);
	carriage = *carriages;
	while (carriage)
	{
		if (!carriage->content->num_cycles_before_op)
			read_arena_to_carriage(carriage->content, params);
		carriage->content->num_cycles_before_op--;
		if (!carriage->content->num_cycles_before_op)
			exec_op(carriage->content, params);
	}
	if (params->cycles_since_start == params->dump_idx)
		; // print memory and quit
	params->cycles_since_last_check++;
}

// 
