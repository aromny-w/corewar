/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 00:00:57 by bgilwood          #+#    #+#             */
/*   Updated: 2020/06/30 22:04:21 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

void	delete_all(t_game_params *params, t_car_list_elem *carriages)
{
	delete_carriage_list(carriages);
	delete_all_players(params->players);
	free(params);
}

void	dump_mem_and_exit(t_game_params *params, t_car_list_elem *carriages)
{
	dump_memory(params->arena);
	delete_all(params, carriages);
	exit(0);
}

void	mem_error_exit()
{
	print_memory_error();
	exit(1);
}

void	game_over(t_game_params *params, t_car_list_elem *carriages)
{
	announce_winner(params);
	delete_all(params, carriages);
	exit(0);
}