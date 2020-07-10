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
	announce_players(params->players);
	play_game(&carriages, params);
	delete_carriage_list(carriages);
	free_params(&params);
	return (0);
}