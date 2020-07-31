/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 17:41:34 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/29 21:55:25 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	announce_winner(t_game_params *params)
{
	int			winning_player;
	char		*winning_player_name;
	t_player	**players;

	winning_player = params->last_alive;
	players = params->players;
	winning_player_name = players[winning_player - 1]->name;
	ft_printf("Contestant %d, \"%s\", has won !\n", winning_player,
	winning_player_name);
}

void	announce_players(t_player **players)
{
	int	i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (players[i])
	{
		ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n",
					players[i]->id, players[i]->code_size,
					players[i]->name, players[i]->comment);
		i++;
	}
}

void	announce_player_alive(t_player **players, int id)
{
	ft_printf("A process shows that player %i (%s) is alive\n",
					id, players[id - 1]->name);
}

/*void	dump_memory(char *arena)
{
	int		i;
	char	c;
	char	*string;
	char	*alphabet;

	alphabet = "0123456789abcdef";
	i = 0;
	while (i < MEM_SIZE)
	{
		c = arena[i];
		string = ft_strnew(3);
		string[0] = alphabet[(((int)c) >> 4) & 15];
		string[1] = alphabet[((int)c) & 15];
		string[2] = ' ';
		ft_putstr(string);
		if (i % 32 == 31)
			ft_putchar('\n');
		i++;
	}
}*/

void	dump_memory(char *arena)
{
	size_t	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % 64))
			ft_printf("0x%04x : ", i);
		ft_printf("%02x ", arena[i] & 0xff);
		if (!(++i % 64) || i == MEM_SIZE)
			ft_printf("\n");
	}
}
