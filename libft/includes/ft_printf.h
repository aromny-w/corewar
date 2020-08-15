/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:55:38 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 22:21:53 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>
# include "libft.h"

typedef struct	s_mods
{
	bool	hh;
	bool	h;
	bool	l;
	bool	ll;
	bool	j;
	bool	t;
	bool	z;
	bool	q;
}				t_mods;

typedef struct	s_flags
{
	bool	hash;
	bool	zero;
	bool	minus;
	bool	space;
	bool	plus;
}				t_flags;

typedef struct	s_pf
{
	int				written;
	struct s_flags	flags;
	int				width;
	int				prec;
	struct s_mods	mods;
	char			spec;
}				t_pf;

int				ft_printf(const char *format, ...);
void			pf_set_flags(const char **format, t_flags *flags);
void			pf_set_width(const char **format, va_list arg, t_pf *info);
void			pf_set_prec(const char **format, va_list arg, t_pf *info);
void			pf_set_mod(const char **format, t_mods *mods);
void			pf_set_spec(const char **format, t_pf *info);
int				pf_form_unknown(t_pf *info);
int				pf_form_percent(t_pf *info);
int				pf_form_integer(va_list arg, t_pf *info);
int				pf_form_unsigned(va_list arg, t_pf *info);
int				pf_form_octal(va_list arg, t_pf *info);
int				pf_form_hexa(va_list arg, t_pf *info);
int				pf_form_float(va_list arg, t_pf *info);
int				pf_form_character(va_list arg, t_pf *info);
int				pf_form_string(va_list arg, t_pf *info);
int				pf_form_pointer(va_list arg, t_pf *info);
int				pf_form_wcharacter(va_list arg, t_pf *info);

#endif
