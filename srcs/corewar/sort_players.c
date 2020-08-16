/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 22:08:28 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/16 22:10:41 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	players_num(t_player *players, int *max_num)
{
	int	i;

	i = 0;
	while (players)
	{
		if (players->id != 0 && players->id > *max_num)
			*max_num = players->id;
		players = players->next;
		i++;
	}
	return (i);
}

static int	get_id(t_player **players, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (!players[i])
			return (i + 1);
		i++;
	}
	return (i + 1);
}

static void	set_players_with_n(t_game_params *prms, t_player *lst)
{
	while (lst)
	{
		if (lst->id)
		{
			if (prms->players[lst->id - 1])
				error("Repeated champions' numbers.", NULL);
			prms->players[lst->id - 1] = lst;
		}
		lst = lst->next;
	}
}

static void	set_rest_players(t_game_params *prms, t_player *lst)
{
	while (lst)
	{
		if (!lst->id)
		{
			lst->id = get_id(prms->players, prms->players_num);
			prms->players[lst->id - 1] = lst;
		}
		lst = lst->next;
	}
}

void		sort_players(t_game_params *prms, t_player **lst, char **av)
{
	int		max_player_num;

	max_player_num = 0;
	if (!(prms->players_num = players_num(*lst, &max_player_num)) \
			|| prms->players_num > MAX_PLAYERS
			|| prms->players_num < max_player_num)
	{
		print_error_msg("Incorrect number of champions: "
						"must be consequent, > 0, <= ", NULL);
		ft_putstr_fd(RED, 2);
		ft_putnbr_fd(MAX_PLAYERS, 2);
		ft_putstr_fd(RESET_COLOR, 2);
		ft_putstr_fd("\n\n", 2);
		print_usage(av[0]);
	}
	if (!(prms->players = (t_player **)ft_memalloc(\
			sizeof(t_player *) * (prms->players_num + 1))))
		error("Malloc failure.", NULL);
	set_players_with_n(prms, *lst);
	set_rest_players(prms, *lst);
	prms->carriages_num = prms->players_num;
	*lst = NULL;
}
