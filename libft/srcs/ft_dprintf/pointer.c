/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dpf_form_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:54:41 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 22:28:13 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void	puthexnbr(t_dpf *info, uintmax_t n, char a)
{
	if (n < 16)
		ft_putchar_fd(n + (n < 10 ? '0' : a - 10), info->fd);
	else
	{
		puthexnbr(info, n / 16, a);
		puthexnbr(info, n % 16, a);
	}
}

static int	nlen(uintmax_t n)
{
	int	len;

	len = 1;
	while (n /= 16)
		len++;
	return (len);
}

static int	print(t_dpf *info, uintmax_t n, int len)
{
	if (info->width > 0 && !info->flags.minus && !info->flags.zero)
		ft_padchar_fd(' ', info->width, info->fd);
	ft_putstr_fd(info->spec != 'X' ? "0x" : "0X", info->fd);
	if (info->prec > 0)
		ft_padchar_fd('0', info->prec, info->fd);
	else if (info->width > 0 && !info->flags.minus && info->flags.zero)
		ft_padchar_fd('0', info->width, info->fd);
	if (!(!n && !info->prec))
		puthexnbr(info, n, info->spec != 'X' ? 'a' : 'A');
	if (info->width > 0 && info->flags.minus)
		ft_padchar_fd(' ', info->width, info->fd);
	return (len + (info->width > 0 ? info->width : 0));
}

int			dform_pointer(va_list arg, t_dpf *info)
{
	uintmax_t	n;
	int			len;

	n = (uintmax_t)va_arg(arg, void *);
	if (!(!n && !info->prec))
	{
		len = nlen(n) > info->prec ? nlen(n) : info->prec;
		info->prec -= nlen(n);
	}
	else
		len = 0;
	len += 2;
	info->width -= len;
	return (print(info, n, len));
}
