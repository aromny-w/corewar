/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   announcements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 17:41:34 by bgilwood          #+#    #+#             */
/*   Updated: 2020/06/28 18:00:05 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

void	announce_winner(t_game_params *params)
{
	int			winning_player;
	char		*winning_player_name;
	t_player	**players;

	winning_player = params->last_alive;
	players = params->players;
	winning_player_name = players[winning_player]->name;
	ft_printf("Player %i (%s) won!!!\n", winning_player, winning_player_name);
}

void	announce_players(t_player **players)
{
	int	i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (players[i])
	{
		ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n",
players[i]->id, players[i]->code_size, players[i]->name, players[i]->comment);
		i++;
	}
}
