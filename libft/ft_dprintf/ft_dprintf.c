/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:02:32 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 22:32:04 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	convert(va_list arg, t_dpf *info)
{
	if (info->spec == '%')
		return (dpf_form_percent(info));
	if (info->spec == 'd' || info->spec == 'i' || info->spec == 'D')
		return (dpf_form_integer(arg, info));
	if (info->spec == 'u' || info->spec == 'U')
		return (dpf_form_unsigned(arg, info));
	if (info->spec == 'o' || info->spec == 'O')
		return (dpf_form_octal(arg, info));
	if (info->spec == 'x' || info->spec == 'X')
		return (dpf_form_hexa(arg, info));
	if (info->spec == 'f' || info->spec == 'F')
		return (dpf_form_float(arg, info));
	if (info->spec == 'c')
		return (dpf_form_character(arg, info));
	if (info->spec == 's' || info->spec == 'S')
		return (dpf_form_string(arg, info));
	if (info->spec == 'p')
		return (dpf_form_pointer(arg, info));
	if (info->spec == 'C')
		return (dpf_form_wcharacter(arg, info));
	return (dpf_form_unknown(info));
}

static int	isattribute(int c)
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

static int	parse(const char **format, va_list arg, t_dpf *info)
{
	int		len;

	(*format)++;
	ft_bzero(&info->flags, sizeof(*info) - sizeof(info->written) -
	sizeof(info->fd));
	info->prec = -1;
	while (isattribute(**format))
	{
		dpf_set_flags(format, &info->flags);
		dpf_set_width(format, arg, info);
		dpf_set_prec(format, arg, info);
		dpf_set_mod(format, &info->mods);
	}
	dpf_set_spec(format, info);
	if (!info->spec || (len = convert(arg, info)) == -1)
		return (-1);
	return (info->written += len);
}

static int	print(int fd, const char *format, va_list arg)
{
	t_dpf	info;

	ft_bzero(&info, sizeof(info));
	info.fd = fd;
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar_fd(*format, info.fd);
			info.written++;
		}
		else if ((parse(&format, arg, &info)) == -1)
			return (info.written);
		format++;
	}
	return (info.written);
}

int			ft_dprintf(int fd, const char *format, ...)
{
	va_list	arg;
	int		done;

	va_start(arg, format);
	done = print(fd, format, arg);
	va_end(arg);
	return (done);
}
