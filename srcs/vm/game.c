/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 00:06:41 by bgilwood          #+#    #+#             */
/*   Updated: 2020/06/30 22:55:48 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <string.h>

void	check_carriages(t_car_list_elem **carriages, t_game_params *params)
{
	t_car_list_elem	*elem;
	t_car_list_elem	*next_elem;
	int				last_man_standing;

	elem = *carriages;
	last_man_standing = elem == NULL;
	while (elem)
	{
		next_elem = elem->next;
		if (params->cycles_since_start - elem->content->last_live >
					params->cycles_to_die)
			delete_carriage_elem(carriages, elem->content->id);
		elem = next_elem;
	}
	if (!elem || elem && !elem->next && last_man_standing)
		game_over(params, *carriages);
	if (params->live_count_in_period > NBR_LIVE
			|| params->checks_count > MAX_CHECKS)
	{
		params->cycles_to_die -= CYCLE_DELTA;
		params->checks_count = 0;
	}
	params->live_count_in_period = 0;
	params->cycles_since_last_check = 0;
}

void	exec_op(t_carriage *carriage, t_game_params *params)
{
	if (carriage->code_op > 16 || carriage->code_op < 1)
	{
		carriage->bytes_next_op = 1;
		return;
	}
	// todo:
	// read args byte, calculate and save carriage->bytes_next_op
	// if args byte valid, call the necessary function
}

void	play_cycle(t_car_list_elem **carriages, t_game_params *params)
{
	t_car_list_elem	*list_elem;

	if (params->cycles_since_last_check > CYCLE_TO_DIE)
		check_carriages(carriages, params);
	list_elem = *carriages;
	while (list_elem)
	{
		if (!list_elem->content->num_cycles_before_op)
			read_arena_to_carriage(list_elem->content, params);
		list_elem->content->num_cycles_before_op--;
		if (!list_elem->content->num_cycles_before_op)
		{
			exec_op(list_elem->content, params);
			move_carriage(list_elem->content,
								list_elem->content->bytes_next_op);
		}
	}
	params->cycles_since_last_check++;
}

void	play_game(t_car_list_elem **carriages, t_game_params *params)
{
	while (1)
	{
		if (params->cycles_since_start == params->dump_idx)
			dump_mem_and_exit(params, *carriages);
		else
			play_cycle(carriages, params);
		params->cycles_since_start++;
	}
}
