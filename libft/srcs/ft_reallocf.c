/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reallocf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 18:30:01 by aromny-w          #+#    #+#             */
/*   Updated: 2020/03/31 22:12:07 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_reallocf(void *ptr, size_t size)
{
	void	*nptr;

	if (!(nptr = realloc(ptr, size)) && size)
		free(ptr);
	return (nptr);
}
