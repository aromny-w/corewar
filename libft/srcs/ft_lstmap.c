/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronika <veronika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:24:46 by aromny-w          #+#    #+#             */
/*   Updated: 2020/06/18 17:47:59 by veronika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	del(void *elem, size_t size)
{
	ft_bzero(elem, size);
	free(elem);
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*list;
	t_list		*list_ptr;

	list = f(lst);
	list_ptr = list;
	while ((lst = lst->next))
	{
		if (!(list_ptr->next = f(lst)))
		{
			ft_lstdel(&list, del);
			return (NULL);
		}
		list_ptr = list_ptr->next;
	}
	return (list);
}
