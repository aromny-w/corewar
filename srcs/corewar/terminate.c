/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 21:54:00 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/01 20:22:07 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	terminate(t_prog *info, int status)
{
	print_error(info, status);
	destroy_struct(info);
	exit(EXIT_FAILURE);
}
