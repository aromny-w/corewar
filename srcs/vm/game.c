/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 00:06:41 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/14 20:06:16 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <string.h>

void	check_carriages(t_car_list_elem **carriages, t_game_params *params)
{
	t_car_list_elem	*elem;
	t_car_list_elem	*next_elem;
	
	if (!carriages || !*carriages)
		error("Memory error, the virtual machine is stopping now.");
	elem = *carriages;
	while (elem)
	{
		next_elem = elem->next;
		if (params->cycles_since_start - elem->content->last_live >
					params->cycles_to_die)
			delete_carriage_elem(carriages, elem->content->id);
		elem = next_elem;
	}
	if (!elem)
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

void	play_cycle(t_car_list_elem **carriages, t_game_params *params)
{
	t_car_list_elem	*list_elem;

	if (!carriages)
		error("wtf");
	if (params->cycles_since_last_check > params->cycles_to_die)
		check_carriages(carriages, params);
	list_elem = *carriages;
	while (list_elem)
	{
		if (!list_elem->content->num_cycles_before_op)
			read_byte_to_carriage(list_elem->content, params);
		list_elem->content->num_cycles_before_op--;
		if (!list_elem->content->num_cycles_before_op)
		{
			exec_op(list_elem->content, params);
			move_carriage(list_elem->content,
								list_elem->content->bytes_next_op);
		}
		list_elem = list_elem->next;
	}
}

void	play_game(t_car_list_elem **carriages, t_game_params *params)
{
	if (!carriages || !*carriages)
		error("Memory error, the virtual machine is stopping now.");
	while (1)
	{
		if (params->cycles_since_start == params->dump_idx
									&& params->dump_flag_on)
			dump_mem_and_exit(params, *carriages);
		else
			play_cycle(carriages, params);
		params->cycles_since_start++;
		params->cycles_since_last_check++;
	}
}
