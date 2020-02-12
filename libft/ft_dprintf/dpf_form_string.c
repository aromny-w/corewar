/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dpf_form_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:53:16 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 22:28:20 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	print(t_dpf *info, char *str, int len)
{
	if (info->width > 0 && !info->flags.minus)
		ft_padchar_fd(!info->flags.zero ? ' ' : '0', info->width, info->fd);
	if ((info->spec != 'S' && !info->mods.l))
		ft_putnstr_fd(str ? str : "(null)", info->prec, info->fd);
	else
		ft_putnwcstr_fd(str ? (wchar_t *)str : L"(null)", info->prec, info->fd);
	if (info->width > 0 && info->flags.minus)
		ft_padchar_fd(' ', info->width, info->fd);
	return (len + (info->width > 0 ? info->width : 0));
}

int			dpf_form_string(va_list arg, t_dpf *info)
{
	char	*str;
	int		len;

	if (info->spec != 'S' && !info->mods.l)
	{
		str = va_arg(arg, char *);
		len = (int)ft_strnlen(str ? str : "(null)", info->prec);
	}
	else
	{
		str = (char *)va_arg(arg, wchar_t *);
		len = (int)ft_wcsnlen(str ? (wchar_t *)str : L"(null)", info->prec);
	}
	info->width -= len;
	return (print(info, str, len));
}
