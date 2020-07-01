/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 23:16:13 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/01 20:12:39 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

t_carriage	*create_carriage(int start_position, int player_id, int id)
{
	t_carriage	*elem;

	elem = (t_carriage*)ft_memalloc(sizeof(t_carriage));
	if (!elem)
		;//error exit
	elem->cur_position = start_position;
	elem->registries[0] = player_id * -1;
	elem->id = id;
}

void		move_carriage(t_carriage *carriage, int distance)
{
	carriage->cur_position = get_new_coord(carriage->cur_position + distance);
}

void		live_carriage(t_carriage *carriage, size_t cycle)
{
	carriage->last_live = cycle;
}

int			get_registry(t_carriage *carriage, int registry_num)
{
	if (registry_num > REG_NUMBER)
		return (-42) ;// just to mess with ppl | error?
	return carriage->registries[registry_num];
}

void		save_registry(t_carriage *carriage, int registry_num, int value)
{
	if (registry_num > REG_NUMBER)
		return ;// error?
	carriage->registries[registry_num] = value;
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
	
	// recalculate carriage->bytes_next_op ?? it seems that no,
	// it needs to be calculated after reading args types byte
	// or while executing the op
}

void		delete_carriage(t_carriage *carriage)
{
	free(carriage);
}
