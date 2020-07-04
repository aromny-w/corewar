#include "vm.h"

t_player		*init_player(char *filename, int num)
{
	t_player	*player;

	if (!(player = (t_player *)ft_memalloc(sizeof(t_player))))
		error("Malloc failure.");
	if (!(player->filename = ft_strdup(filename)))
		error("Malloc failure.");
	player->id = num;
	return (player);
}

t_game_params	*init_game_params(void)
{
	t_game_params	*params;

	if (!(params = (t_game_params *)ft_memalloc(sizeof(t_game_params))))
		error("Malloc failure.");
	params->cycles_to_die = CYCLE_TO_DIE;
	return (params);
}