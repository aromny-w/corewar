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
		error("Pointer is not initialized.", NULL);
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
	int		num;
	char	*compare_num;

	if (params->dump_flag_on || ++*i == ac)
		print_usage(av[0]);
	num = ft_atoi(av[*i]);
	compare_num = ft_itoa(num);
	if ((num < 0) || !ft_strequ(av[*i], compare_num))
	{
		print_error_msg("Incorrect dump number.\n", NULL);
		print_usage(av[0]);
	}
	params->dump_idx = num;
	params->dump_flag_on = 1;
	ft_strdel(&compare_num);
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
	char		*compare_num;

	if (++*i == ac)
		print_usage(av[0]);
	num = ft_atoi(av[*i]);
	compare_num = ft_itoa(num);
	if (num <= 0 || num > MAX_PLAYERS ||
				!ft_strequ(av[*i], compare_num) || (++*i == ac))
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("ERROR: Incorrect "
				"champion's -n number: must be from 1 to ", 2);
		ft_putnbr_fd(MAX_PLAYERS, 2);
		ft_putstr_fd(".\n\n", 2);
		ft_putstr_fd(RESET_COLOR, 2);
		print_usage(av[0]);
	}
	player = init_player(av[*i], num);
	push_player(players, player);
	ft_strdel(&compare_num);
}

void		get_args(int ac, char **av, t_game_params *params)
{
	int			i;
	t_player	*players;
	char		*check;

	i = 0;
	players = NULL;
	while (++i < ac && (check = av[i]))
	{
		if (ft_strequ(check, "-dump"))
			set_dump(ac, av, &i, params);
		else if (ft_strequ(av[i], "-n"))
			put_n_player(ac, av, &i, &players);
		else if (ft_strequ(av[i], "-s"))
			params->s_flag_on = 1;
		else if (ft_strequ(av[i], "-v"))
			params->v_flag_on = 1;
		else if (ft_strstr(av[i], ".cor"))
			put_player(av, &i, &players);
		else
			print_usage(av[0]);
	}
	sort_players(params, &players, av);
	params->last_alive = params->players_num;
}
