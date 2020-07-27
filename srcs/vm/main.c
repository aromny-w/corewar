/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 22:12:59 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/24 21:15:37 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			main(int ac, char **av)
{
	t_game_params	*params;
	t_car_list_elem	*carriages;

	if (ac < 2)
		print_usage(av[0]);
	params = init_game_params();
	get_args(ac, av, params);
	validate_players(av, params);
	params->arena = arena_init();
	carriages = place_players(params->players, params->arena);
	params->carriages_list = carriages;
	announce_players(params->players);
	play_game(params);
	delete_carriage_list(carriages);
	free_params(&params);
	return (0);
}
