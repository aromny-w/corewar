/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:29:02 by aromny-w          #+#    #+#             */
/*   Updated: 2018/12/10 17:29:05 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_dcount(int n)
{
	int	count;

	count = 1;
	while (n /= 10)
		count++;
	return (count);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		len;
	int		i;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if ((sign = n) < 0)
		n = -n;
	len = get_dcount(n) + (sign < 0 ? 1 : 0);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	str[i++] = n % 10 + '0';
	while (n /= 10)
		str[i++] = n % 10 + '0';
	if (sign < 0)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
}
