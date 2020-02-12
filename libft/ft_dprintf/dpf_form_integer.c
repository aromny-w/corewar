/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dpf_form_integer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:41:51 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 22:27:49 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void		putunbr(t_dpf *info, uintmax_t n)
{
	if (n < 10)
		ft_putchar_fd(n + '0', info->fd);
	else
	{
		putunbr(info, n / 10);
		putunbr(info, n % 10);
	}
}

static int		nlen(intmax_t n)
{
	int	len;

	len = 1;
	while (n /= 10)
		len++;
	return (len);
}

static int		print(t_dpf *info, intmax_t n, int len)
{
	if (info->width > 0 && !info->flags.minus && !info->flags.zero)
		ft_padchar_fd(' ', info->width, info->fd);
	if (n < 0)
		ft_putchar_fd('-', info->fd);
	else if (info->flags.space || info->flags.plus)
		ft_putchar_fd(info->flags.space ? ' ' : '+', info->fd);
	if (info->prec > 0)
		ft_padchar_fd('0', info->prec, info->fd);
	else if (info->width > 0 && !info->flags.minus && info->flags.zero)
		ft_padchar_fd('0', info->width, info->fd);
	if (len)
		putunbr(info, n < 0 ? -n : n);
	if (info->width > 0 && info->flags.minus)
		ft_padchar_fd(' ', info->width, info->fd);
	return (len + (info->width > 0 ? info->width : 0));
}

static intmax_t	cast(intmax_t n, t_mods mods, char spec)
{
	if (spec == 'D')
		return ((long)n);
	else if (mods.q)
		return ((quad_t)n);
	else if (mods.z)
		return ((size_t)n);
	else if (mods.t)
		return ((ptrdiff_t)n);
	else if (mods.j)
		return ((intmax_t)n);
	else if (mods.ll)
		return ((long long)n);
	else if (mods.l)
		return ((long)n);
	else if (mods.h)
		return ((short)n);
	else if (mods.hh)
		return ((signed char)n);
	return ((int)n);
}

int				dpf_form_integer(va_list arg, t_dpf *info)
{
	intmax_t	n;
	int			len;

	n = cast(va_arg(arg, intmax_t), info->mods, info->spec);
	len = 0;
	if (!(!n && !info->prec))
	{
		if ((len = nlen(n)) < info->prec)
			len = info->prec;
		if (n < 0 || info->flags.plus || info->flags.space)
			len++;
		info->width -= len;
		info->prec -= nlen(n);
	}
	else
		info->width -= info->flags.space;
	return (print(info, n, len));
}
