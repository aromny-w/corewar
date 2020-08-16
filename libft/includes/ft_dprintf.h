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
# include "libft.h"

typedef struct	s_dmods
{
	bool	hh;
	bool	h;
	bool	l;
	bool	ll;
	bool	j;
	bool	t;
	bool	z;
	bool	q;
}				t_dmods;

typedef struct	s_dflags
{
	bool	hash;
	bool	zero;
	bool	minus;
	bool	space;
	bool	plus;
}				t_dflags;

typedef struct	s_dpf
{
	int				written;
	int				fd;
	struct s_dflags	flags;
	int				width;
	int				prec;
	struct s_dmods	mods;
	char			spec;
}				t_dpf;

int				ft_dprintf(int fd, const char *format, ...);
void			dset_flags(const char **format, t_dflags *flags);
void			dset_width(const char **format, va_list arg, t_dpf *info);
void			dset_prec(const char **format, va_list arg, t_dpf *info);
void			dset_mod(const char **format, t_dmods *mods);
void			dset_spec(const char **format, t_dpf *info);
int				dform_unknown(t_dpf *info);
int				dform_percent(t_dpf *info);
int				dform_integer(va_list arg, t_dpf *info);
int				dform_unsigned(va_list arg, t_dpf *info);
int				dform_octal(va_list arg, t_dpf *info);
int				dform_hexa(va_list arg, t_dpf *info);
int				dform_float(va_list arg, t_dpf *info);
int				dform_character(va_list arg, t_dpf *info);
int				dform_string(va_list arg, t_dpf *info);
int				dform_pointer(va_list arg, t_dpf *info);
int				dform_wcharacter(va_list arg, t_dpf *info);

#endif
