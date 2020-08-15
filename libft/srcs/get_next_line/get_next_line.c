/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 14:58:34 by aromny-w          #+#    #+#             */
/*   Updated: 2019/01/04 16:57:06 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*get_list(const int fd, t_list **lst)
{
	t_list			*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->content_size == (size_t)fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("", 1);
	tmp->content_size = (size_t)fd;
	ft_lstadd(lst, tmp);
	return (tmp);
}

static int		get_line(char **line, char **content)
{
	char			*str;
	size_t			len;
	size_t			i;

	if (!(len = ft_strlen(*content)))
		return (0);
	i = 0;
	while ((*content)[i] && (*content)[i] != '\n')
		i++;
	if (!(*line = ft_strsub(*content, 0, i)))
		return (-1);
	if (!(*content)[i])
	{
		ft_strclr(*content);
		return (1);
	}
	str = ft_strsub(*content, (unsigned int)(i + 1), len - i - 1);
	ft_strdel(content);
	*content = ft_strdup(str);
	ft_strdel(&str);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	t_list			*tmp;
	char			*buf;
	char			*str;
	long			ret;

	if (!line || read(fd, 0, 0) == -1 ||
	!(buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	tmp = get_list(fd, &lst);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(str = ft_strjoin(tmp->content, buf)))
			return (-1);
		ft_strdel((char **)&tmp->content);
		tmp->content = ft_strdup(str);
		ft_strdel(&str);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	ft_strdel(&buf);
	return (ret != -1 ? get_line(line, (char **)&tmp->content) : -1);
}
