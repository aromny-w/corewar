/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:05:05 by malannys          #+#    #+#             */
/*   Updated: 2020/08/03 18:05:10 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

void	error(char *str)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("ERROR: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(RESET_COLOR, 2);
	write(2, "\n", 1);
	exit(1);
}
