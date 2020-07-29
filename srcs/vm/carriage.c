/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 23:16:13 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/28 22:47:23 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void		move_carriage(t_carriage *carriage, int distance)
{
	carriage->cur_position = get_new_coord(carriage->cur_position + distance);
	carriage->bytes_next_op = 0;
}

void		live_carriage(t_carriage *carriage, size_t cycle)
{
	carriage->last_live = cycle;
}

int			get_registry(t_carriage *carriage, int registry_num)
{
	if (registry_num > REG_NUMBER || registry_num < 0)
		return (-42);
	return (carriage->registries[registry_num - 1]);
}

void		save_registry(t_carriage *carriage, int registry_num, int value)
{
	if (registry_num > REG_NUMBER || registry_num < 1)
		return ;
	carriage->registries[registry_num - 1] = value;
}

void		read_byte_to_carriage(t_carriage *carriage, t_game_params *arena)
{
	carriage->code_op = arena_read_byte(arena->arena, carriage->cur_position);
	if (carriage->code_op > 0 && carriage->code_op < 17)
	{
		carriage->num_cycles_before_op = g_op_tab[carriage->code_op - 1].cycle;
	}
	else
	{
		carriage->bytes_next_op = 1;
	}
}
