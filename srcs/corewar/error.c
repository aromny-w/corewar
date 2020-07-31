/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 22:06:02 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/16 22:07:12 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error(char *str)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("\nERROR: ", 2);
	if (errno)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(2, " ", 1);
	}
	ft_putstr_fd(str, 2);
	ft_putstr_fd(RESET_COLOR, 2);
	write(2, "\n", 1);
	exit(1);
}
