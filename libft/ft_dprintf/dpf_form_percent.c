/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dpf_form_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 20:37:40 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 22:28:05 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	print(t_dpf *info, int len)
{
	if (info->width > 0 && !info->flags.minus)
		ft_padchar_fd(!info->flags.zero ? ' ' : '0', info->width, info->fd);
	ft_putchar_fd('%', info->fd);
	if (info->width > 0 && info->flags.minus)
		ft_padchar_fd(' ', info->width, info->fd);
	return (len + (info->width > 0 ? info->width : 0));
}

int			dpf_form_percent(t_dpf *info)
{
	int	len;

	len = 1;
	info->width--;
	return (print(info, len));
}
