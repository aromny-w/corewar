/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 00:13:23 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/01 22:12:10 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		place_player_code(char *arena, int position, char *code,
															int size)
{
	ft_memmove(arena + position, code, size);
}

t_car_list_elem	*place_players(t_player **players, char *arena)
{
	int				num_players;
	int				player_len;
	int				i;
	t_car_list_elem	*list;

	num_players = 0;
	while (players[num_players])
		num_players++;
	player_len = MEM_SIZE / num_players;
	i = 0;
	list = NULL;
	while (i < num_players)
	{
		add_carriage_elem(&list, i * player_len, i + 1, i + 1);
		place_player_code(arena, i * player_len, players[i]->code,
							players[i]->code_size);
		i++;
	}
	return (list);
}

void			delete_all_players(t_player **players)
{
	int i;

	i = 0;
	while (players[i])
	{
		free(players[i]->code);
		free(players[i]->name);
		free(players[i]->comment);
		free(players[i]);
		i++;
	}
	free(players);
}
