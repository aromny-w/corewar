/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 00:06:41 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/29 23:55:45 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_carriages(t_car_list_elem **carriages, t_game_params *params)
{
	t_car_list_elem	*elem;
	t_car_list_elem	*next_elem;

	if (!carriages)
		error("Memory error, the virtual machine is stopping now.");
	elem = *carriages;
	while (elem)
	{
		next_elem = elem->next;
		if (params->cycles_since_start - elem->content->last_live >=
					params->cycles_to_die)
			delete_carriage_elem(carriages, elem->content->id);
		elem = next_elem;
	}
	if (!*carriages || params->cycles_to_die < 0)
		game_over(params, *carriages);
	if (params->live_count_in_period > NBR_LIVE
			|| params->checks_count == MAX_CHECKS)
	{
		params->cycles_to_die -= CYCLE_DELTA;
		params->checks_count = 0;
	}
	params->checks_count++;
	params->live_count_in_period = 0;
	params->cycles_since_last_check = 0;
}

void	play_cycle(t_game_params *params)
{
	t_car_list_elem	*list_elem;

	list_elem = params->carriages_list;
	while (list_elem)
	{
		if (!list_elem->content->num_cycles_before_op)
			read_byte_to_carriage(list_elem->content, params);
		if (list_elem->content->num_cycles_before_op > 0)
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

void	play_game(t_game_params *params)
{
	while (true)
	{
		if (params->cycles_since_last_check >= params->cycles_to_die)
			check_carriages(&(params->carriages_list), params);
		if (params->cycles_since_start == params->dump_idx
									&& params->dump_flag_on)
			dump_mem_and_exit(params, params->carriages_list);
		else
			play_cycle(params);
		params->cycles_since_start++;
		params->cycles_since_last_check++;
	}
}
