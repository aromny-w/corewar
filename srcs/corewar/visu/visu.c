/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:21:45 by aromny-w          #+#    #+#             */
/*   Updated: 2020/08/19 11:21:46 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	destroy(t_game_params *params)
{
	if (params->visu->win_ptr)
		mlx_destroy_window(params->visu->mlx_ptr, params->visu->win_ptr);
	delete_carriage_list(params->carriages_list);
	free_params(&params);
	exit(EXIT_SUCCESS);
}

static int	visu_hook(t_game_params *params)
{
	draw_arena(params);
	play_cycle(params);
	params->cycles_since_start++;
	params->cycles_since_last_check++;
	return (0);
}

static int	exit_key(int key, t_game_params *params)
{
	if (key == 53)
		destroy(params);
	return (1);
}

int			get_color(int id)
{
	if (id == 1)
		return (GREEN_COLOR);
	if (id == 2)
		return (BLUE_COLOR);
	if (id == 3)
		return (RED_COLOR);
	if (id == 4)
		return (AQUA_COLOR);
	return (0);
}

void		visualise(t_game_params *params)
{
	params->visu = init_visu(params);
	mlx_key_hook(params->visu->win_ptr, exit_key, params);
	mlx_loop_hook(params->visu->mlx_ptr, visu_hook, params);
	mlx_hook(params->visu->win_ptr, 17, 1L << 17, destroy, params);
	mlx_loop(params->visu->mlx_ptr);
}
