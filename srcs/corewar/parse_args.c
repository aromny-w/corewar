/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 22:14:29 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/16 22:26:37 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	push_player(t_player **head, t_player *player)
{
	t_player	*tmp;

	if (!head)
		error("Pointer is not initialized.");
	if (!*head)
	{
		*head = player;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = player;
}

static void	set_dump(int ac, char **av, int *i, t_game_params *params)
{
	int	num;

	if (++*i == ac)
		print_usage(av[0]);
	if ((num = ft_atoi(av[*i]) >= 0))
	{
		params->dump_idx = num;
		params->dump_flag_on = 1;
	}
	else
		print_usage(av[0]);
}

static void	put_player(char **av, int *i, t_player **players)
{
	t_player	*player;

	player = init_player(av[*i], 0);
	push_player(players, player);
}

static void	put_n_player(int ac, char **av, int *i, t_player **players)
{
	int			num;
	t_player	*player;

	if (++*i < ac)
	{
		num = ft_atoi(av[*i]);
		if (ft_strequ(av[*i], ft_itoa(num)) && num > 0 && (++*i < ac))
		{
			player = init_player(av[*i], num);
			push_player(players, player);
			return ;
		}
	}
	print_usage(av[0]);
}

void		get_args(int ac, char **av, t_game_params *params)
{
	int			i;
	t_player	*players;
	char		*check;

	i = 0;
	players = NULL;
	while (++i < ac)
	{
		check = av[i];
		if (ft_strequ(check, "-dump"))
			set_dump(ac, av, &i, params);
		else if (ft_strequ(av[i], "-n"))
			put_n_player(ac, av, &i, &players);
		else if (ft_strequ(av[i], "-a"))
			params->a_flag_on = 1;
		else if (ft_strstr(av[i], ".cor"))
			put_player(av, &i, &players);
		else
			print_usage(av[0]);
	}
	sort_players(params, &players);
	params->last_alive = params->players_num;
}
