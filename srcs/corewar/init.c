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

#include "corewar.h"

static void		set_color(int *color, t_game_params *params)
{
	size_t	num_players;
	size_t	offset;
	int		i;

	ft_memset(color, 0x808080, sizeof(int) * MEM_SIZE);
	num_players = 0;
	while (params->players[num_players])
		num_players++;
	offset = MEM_SIZE / num_players;
	if (num_players > 0 && !(i = 0))
		while (i < params->players[0]->code_size)
			color[i++] = get_color(params->players[0]->id);
	if (num_players > 1 && !(i = 0))
		while (i < params->players[1]->code_size)
			color[offset + i++] = get_color(params->players[1]->id);
	if (num_players > 2 && !(i = 0))
		while (i < params->players[2]->code_size)
			color[offset * 2 + i++] = get_color(params->players[2]->id);
	if (num_players > 3 && !(i = 0))
		while (i < params->players[3]->code_size)
			color[offset * 3 + i++] = get_color(params->players[3]->id);
}

t_mlx			*init_visu(t_game_params *params)
{
	t_mlx	*visu;

	if (!(visu = ft_memalloc(sizeof(t_mlx))))
		error(NULL, NULL);
	if (!(visu->mlx_ptr = mlx_init()))
		error(NULL, NULL);
	visu->width = 1600;
	visu->height = 1280;
	if (!(visu->win_ptr = mlx_new_window(visu->mlx_ptr, visu->width,
	visu->height, "corewar")))
		error(NULL, NULL);
	set_color(visu->color, params);
	return (visu);
}

t_player		*init_player(char *filename, int num)
{
	t_player	*player;

	if (!(player = (t_player *)ft_memalloc(sizeof(t_player))))
		error("Malloc failure.", NULL);
	if (!(player->filename = ft_strdup(filename)))
		error("Malloc failure.", NULL);
	player->id = num;
	return (player);
}

t_game_params	*init_game_params(void)
{
	t_game_params	*params;

	if (!(params = (t_game_params *)ft_memalloc(sizeof(t_game_params))))
		error("Malloc failure.", NULL);
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
