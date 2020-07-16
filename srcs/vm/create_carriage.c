/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_carriage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:04:09 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/16 22:02:45 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_carriage	*create_carriage(int start_position, int player_id, int id)
{
	t_carriage	*elem;

	elem = (t_carriage*)ft_memalloc(sizeof(t_carriage));
	if (!elem)
		error("Memory error, the virtual machine is stopping now.");
	elem->cur_position = start_position;
	elem->registries[0] = player_id * -1;
	elem->id = id;
	return (elem);
}

t_carriage	*duplicate_carriage(t_carriage *original, int new_id,
														int new_position)
{
	t_carriage	*copy;

	new_position = get_new_coord(new_position);
	copy = create_carriage(new_position, 0, new_id);
	copy->carry = original->carry;
	ft_memcpy(copy->registries, original->registries, sizeof(int) * REG_NUMBER);
	copy->last_live = original->last_live;
	return (copy);
}
