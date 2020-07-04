/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 01:03:13 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/05 01:07:58 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrdel(char ***array)
{
	int i;

	if (!array || !*array)
		return ;
	i = 0;
	while (array [0][i])
	{
		free(array[0][i]);
		i++;
	}
	free(*array);
	*array = NULL;
}