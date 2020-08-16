/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:02:32 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 21:49:50 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	convert(va_list arg, t_pf *info)
{
	if (info->spec == '%')
		return (form_percent(info));
	if (info->spec == 'd' || info->spec == 'i' || info->spec == 'D')
		return (form_integer(arg, info));
	if (info->spec == 'u' || info->spec == 'U')
		return (form_unsigned(arg, info));
	if (info->spec == 'o' || info->spec == 'O')
		return (form_octal(arg, info));
	if (info->spec == 'x' || info->spec == 'X')
		return (form_hexa(arg, info));
	if (info->spec == 'f' || info->spec == 'F')
		return (form_float(arg, info));
	if (info->spec == 'c')
		return (form_character(arg, info));
	if (info->spec == 's' || info->spec == 'S')
		return (form_string(arg, info));
	if (info->spec == 'p')
		return (form_pointer(arg, info));
	if (info->spec == 'C')
		return (form_wcharacter(arg, info));
	return (form_unknown(info));
}

static int	is_attribute(int c)
{
	if (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+')
		return (1);
	if (ft_isdigit(c) || c == '*' || c == '.')
		return (1);
	if (c == 'h' || c == 'l' || c == 'j' || c == 't' || c == 'z' || c == 'q' ||
		c == 'L')
		return (1);
	return (0);
}

static int	parse(const char **format, va_list arg, t_pf *info)
{
	int		len;

	(*format)++;
	ft_bzero(&info->flags, sizeof(*info) - sizeof(info->written));
	info->prec = -1;
	while (is_attribute(**format))
	{
		set_flags(format, &info->flags);
		set_width(format, arg, info);
		set_prec(format, arg, info);
		set_mod(format, &info->mods);
	}
	set_spec(format, info);
	if (!info->spec || (len = convert(arg, info)) == -1)
		return (-1);
	return (info->written += len);
}

static int	print(const char *format, va_list arg)
{
	t_pf	info;

	ft_bzero(&info, sizeof(info));
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar(*format);
			info.written++;
		}
		else if ((parse(&format, arg, &info)) == -1)
			return (info.written);
		format++;
	}
	return (info.written);
}

int			ft_printf(const char *format, ...)
{
	va_list	arg;
	int		done;

	va_start(arg, format);
	done = print(format, arg);
	va_end(arg);
	return (done);
}
