/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:55:38 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 22:36:34 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>
# include "ft_printf.h"
# include "libft.h"

typedef struct	s_dpf
{
	int				written;
	int				fd;
	struct s_flags	flags;
	int				width;
	int				prec;
	struct s_mods	mods;
	char			spec;
}				t_dpf;

int				ft_dprintf(int fd, const char *format, ...);
void			dpf_set_flags(const char **format, t_flags *flags);
void			dpf_set_width(const char **format, va_list arg, t_dpf *info);
void			dpf_set_prec(const char **format, va_list arg, t_dpf *info);
void			dpf_set_mod(const char **format, t_mods *mods);
void			dpf_set_spec(const char **format, t_dpf *info);
int				dpf_form_unknown(t_dpf *info);
int				dpf_form_percent(t_dpf *info);
int				dpf_form_integer(va_list arg, t_dpf *info);
int				dpf_form_unsigned(va_list arg, t_dpf *info);
int				dpf_form_octal(va_list arg, t_dpf *info);
int				dpf_form_hexa(va_list arg, t_dpf *info);
int				dpf_form_float(va_list arg, t_dpf *info);
int				dpf_form_character(va_list arg, t_dpf *info);
int				dpf_form_string(va_list arg, t_dpf *info);
int				dpf_form_pointer(va_list arg, t_dpf *info);
int				dpf_form_wcharacter(va_list arg, t_dpf *info);

#endif
