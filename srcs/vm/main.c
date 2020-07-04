#include "vm.h"

int			main(int ac, char **av)
{
	t_game_params	*params;

	if (ac < 2)
		print_usage(av[0]);
	params = init_game_params();
	get_args(ac, av, params);
	validate_players(av, params);
	free_params(&params);
	return (0);
}