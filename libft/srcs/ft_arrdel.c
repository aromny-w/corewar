/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:05:05 by malannys          #+#    #+#             */
/*   Updated: 2020/08/03 18:05:10 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrdel(char ***arr)
{
	size_t	i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while (*(*arr + i))
	{
		free(*(*arr + i));
		*(*arr + i) = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}
