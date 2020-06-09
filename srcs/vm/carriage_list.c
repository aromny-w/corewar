/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 23:35:30 by bgilwood          #+#    #+#             */
/*   Updated: 2020/06/09 23:12:16 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	add_carriage_elem(t_car_list_elem **head,
					int car_position, int player_id, int id)
{
	t_carriage		*new_carriage;
	t_car_list_elem	*new_elem;

	if (!head)
		return;
	new_carriage = create_carriage(car_position, player_id, id);
	new_elem = (t_car_list_elem*)ft_memalloc(sizeof(t_car_list_elem));
	if (!new_elem)
		;//error exit
	if (*head)
		new_elem->next = *head;
	new_elem->content = new_carriage;
	*head = new_elem;
}

void	delete_carriage_elem(t_car_list_elem **head, int id)
{
	t_car_list_elem	*prev;
	t_car_list_elem	*to_delete;

	prev = *head;
	if (prev->content->id == id)
	{
		*head = prev->next;
		to_delete = prev;
	}
	else
	{
		while (prev->next && prev->next->content->id != id)
			prev = prev->next;
		to_delete = prev->next;
		if (prev->next->next)
			prev->next = prev->next->next;
	}
	delete_carriage(to_delete->content);
	free(to_delete);
}
