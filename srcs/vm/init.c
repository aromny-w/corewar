/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 22:17:25 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/16 22:12:38 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void (*g_execs[])(t_carriage*, t_game_params*, int) =
{
	op_live,
	op_ld,
	op_st,
	op_add,
	op_sub,
	op_and,
	op_or,
	op_xor,
	op_zjmp,
	op_ldi,
	op_sti,
	op_fork,
	op_lld,
	op_lldi,
	op_lfork,
	op_aff
};
