/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dpf_form_wcharacter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 20:47:09 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 22:28:39 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	print(t_dpf *info, wchar_t wc, int len)
{
	if (info->width > 0 && !info->flags.minus)
		ft_padchar_fd(!info->flags.zero ? ' ' : '0', info->width, info->fd);
	ft_putwchar_fd(wc, info->fd);
	if (info->width > 0 && info->flags.minus)
		ft_padchar_fd(' ', info->width, info->fd);
	return (len + (info->width > 0 ? info->width : 0));
}

int			dpf_form_wcharacter(va_list arg, t_dpf *info)
{
	wchar_t	wc;
	int		len;

	wc = va_arg(arg, wchar_t);
	if (wc < 128)
		len = 1;
	else if (wc < 2048)
		len = 2;
	else if (wc < 65536)
		len = 3;
	else
		len = 4;
	info->width -= len;
	return (print(info, wc, len));
}
