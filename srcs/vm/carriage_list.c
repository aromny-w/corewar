/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 23:35:30 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/16 22:11:14 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	add_carriage_elem(t_car_list_elem **head,
					int car_position, int player_id, int id)
{
	t_carriage		*new_carriage;

	if (!head)
		return ;
	new_carriage = create_carriage(car_position, player_id, id);
	insert_existing_carriage(head, new_carriage);
}

void	insert_existing_carriage(t_car_list_elem **head, t_carriage *elem)
{
	t_car_list_elem	*new_elem;

	if (!head)
		return ;
	new_elem = (t_car_list_elem*)ft_memalloc(sizeof(t_car_list_elem));
	if (!new_elem)
		error("Memory error, the virtual machine is stopping now.");
	if (*head)
		new_elem->next = *head;
	new_elem->content = elem;
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

void	delete_carriage_list(t_car_list_elem *head)
{
	t_car_list_elem	*elem;
	t_car_list_elem	*next;

	elem = head;
	while (elem)
	{
		next = elem->next;
		delete_carriage(elem->content);
		free(elem);
		elem = next;
	}
}
