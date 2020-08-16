/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dpf_form_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:44:01 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 22:28:33 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void			putunbr(t_dpf *info, uintmax_t n)
{
	if (n < 10)
		ft_putchar_fd(n + '0', info->fd);
	else
	{
		putunbr(info, n / 10);
		putunbr(info, n % 10);
	}
}

static int			nlen(uintmax_t n)
{
	int	len;

	len = 1;
	while (n /= 10)
		len++;
	return (len);
}

static int			print(t_dpf *info, uintmax_t n, int len)
{
	if (info->width > 0 && !info->flags.minus && !info->flags.zero)
		ft_padchar_fd(' ', info->width, info->fd);
	if (info->prec > 0)
		ft_padchar_fd('0', info->prec, info->fd);
	else if (info->width > 0 && !info->flags.minus && info->flags.zero)
		ft_padchar_fd('0', info->width, info->fd);
	if (len)
		putunbr(info, n);
	if (info->width > 0 && info->flags.minus)
		ft_padchar_fd(' ', info->width, info->fd);
	return (len + (info->width > 0 ? info->width : 0));
}

static uintmax_t	cast(uintmax_t n, t_dmods mods, char spec)
{
	if (spec == 'U')
		return ((unsigned long)n);
	else if (mods.q)
		return ((u_quad_t)n);
	else if (mods.z)
		return ((size_t)n);
	else if (mods.t)
		return ((ptrdiff_t)n);
	else if (mods.j)
		return ((uintmax_t)n);
	else if (mods.ll)
		return ((unsigned long long)n);
	else if (mods.l)
		return ((unsigned long)n);
	else if (mods.h)
		return ((unsigned short)n);
	else if (mods.hh)
		return ((unsigned char)n);
	return ((unsigned int)n);
}

int					dform_unsigned(va_list arg, t_dpf *info)
{
	uintmax_t	n;
	int			len;

	n = cast(va_arg(arg, uintmax_t), info->mods, info->spec);
	len = 0;
	if (!(!n && !info->prec))
	{
		len = nlen(n) > info->prec ? nlen(n) : info->prec;
		info->width -= len;
		info->prec -= nlen(n);
	}
	else
		info->width -= info->flags.space;
	return (print(info, n, len));
}
