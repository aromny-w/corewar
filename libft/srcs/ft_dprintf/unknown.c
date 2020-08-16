/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dpf_form_unknown.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 19:42:16 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 22:28:27 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	print(t_dpf *info, int c, int len)
{
	if (info->width > 0 && !info->flags.minus)
		ft_padchar_fd(!info->flags.zero ? ' ' : '0', info->width, info->fd);
	ft_putchar_fd(c, info->fd);
	if (info->width > 0 && info->flags.minus)
		ft_padchar_fd(' ', info->width, info->fd);
	return (len + (info->width > 0 ? info->width : 0));
}

int			dform_unknown(t_dpf *info)
{
	int	len;

	len = 1;
	info->width--;
	return (print(info, info->spec, len));
}
