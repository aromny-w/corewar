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

#include "vm.h"

static int	players_num(t_player *players)
{
	int	i;

	i = 0;
	while (players)
	{
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
				error("Repeated champions' numbers.");
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

void		sort_players(t_game_params *prms, t_player **lst)
{
	if (!(prms->players_num = players_num(*lst)) \
			|| prms->players_num > MAX_PLAYERS)
		error("Incorrect number of champions.");
	if (!(prms->players = (t_player **)ft_memalloc(\
			sizeof(t_player *) * (prms->players_num + 1))))
		error("Malloc failure.");
	set_players_with_n(prms, *lst);
	set_rest_players(prms, *lst);
	prms->carriages_num = prms->players_num;
	*lst = NULL;
}
