/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dpf_form_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:16:28 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 22:27:33 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void		putnbr(t_dpf *info, uintmax_t n)
{
	if (n < 10)
		ft_putchar_fd(n + '0', info->fd);
	else
	{
		putnbr(info, n / 10);
		putnbr(info, n % 10);
	}
}

static void		putfltnbr(t_dpf *info, long double n)
{
	n = n < 0 ? -n : n;
	n += 5L / ft_powl(10L, info->prec + 1);
	putnbr(info, n);
	n -= (uintmax_t)n;
	if (info->prec || info->flags.hash)
	{
		ft_putchar_fd('.', info->fd);
		while (info->prec--)
		{
			ft_putchar_fd((uintmax_t)(n *= 10L) + '0', info->fd);
			n -= (uintmax_t)n;
		}
	}
}

static int		nlen(long long n)
{
	int	len;

	len = 1;
	while (n /= 10)
		len++;
	return (len);
}

static int		print(t_dpf *info, long double n, int len)
{
	if (info->width > 0 && !info->flags.minus && (!info->flags.zero || n != n))
		ft_padchar_fd(' ', info->width, info->fd);
	if (n < 0)
		ft_putchar_fd('-', info->fd);
	else if (n == n && (info->flags.space || info->flags.plus))
		ft_putchar_fd(info->flags.space ? ' ' : '+', info->fd);
	if (n == n && info->width > 0 && !info->flags.minus && info->flags.zero)
		ft_padchar_fd('0', info->width, info->fd);
	if (n == n && n != n / 0)
		putfltnbr(info, n);
	else if (n != n)
		ft_putstr(info->spec != 'F' ? "nan" : "NAN");
	else if (n == n / 0)
		ft_putstr(info->spec != 'F' ? "inf" : "INF");
	if (info->width > 0 && info->flags.minus)
		ft_padchar_fd(' ', info->width, info->fd);
	return (len + (info->width > 0 ? info->width : 0));
}

int				dform_float(va_list arg, t_dpf *info)
{
	long double	n;
	int			len;

	if (!info->mods.ll)
		n = va_arg(arg, double);
	else
		n = va_arg(arg, long double);
	if (n == n && n != n / 0)
		len = nlen(n) + (!info->prec ? 0 : info->prec + 1);
	else
		len = 3;
	if (n == n && (n < 0 || info->flags.plus || info->flags.space))
		len++;
	info->width -= len;
	return (print(info, n, len));
}
