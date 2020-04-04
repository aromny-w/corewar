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

#include "asm.h"

void		terminate(t_asm *info, int status, t_token *token)
{
	(void)info;
	(void)status;
	(void)token;
	destroy_struct(info);
	exit(EXIT_FAILURE);
}
