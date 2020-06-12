/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 00:08:30 by aromny-w          #+#    #+#             */
/*   Updated: 2020/05/04 00:08:31 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_comment(char *s)
{
	int	i;

	i = 0;
	while (s[++i])
		if (s[i] == '\n')
			break ;
	return (ft_strndup(s, i));
}

static char	*get_whitespace(char *s)
{
	int	i;

	i = 0;
	while (s[++i])
		if (!ft_isspace(s[i]) || s[i] == '\n')
			break ;
	return (ft_strndup(s, i));
}

static char	*get_string(char *s)
{
	int	i;

	i = 1;
	while (s[i])
		if (s[i++] == STRING_CHAR)
			break ;
	return (ft_strndup(s, i));
}

static char	*get_command(char *s)
{
	size_t	len;

	if (!ft_strncmp(s, NAME_CMD_STRING, len = ft_strlen(NAME_CMD_STRING)))
		return (ft_strndup(s, len));
	if (!ft_strncmp(s, COMMENT_CMD_STRING, len = ft_strlen(COMMENT_CMD_STRING)))
		return (ft_strndup(s, len));
	return (NULL);
}

char		*get_token_str(char *s)
{
	int	i;

	if (*s == COMMAND_CHAR)
		return (get_command(s));
	if (*s == STRING_CHAR)
		return (get_string(s));
	if (*s == SEPARATOR_CHAR || *s == '\n')
		return (ft_strndup(s, 1));
	if (*s == COMMENT_CHAR || *s == COMMENT_CHAR_2)
		return (get_comment(s));
	if (ft_isspace(*s))
		return (get_whitespace(s));
	i = 0;
	if (s[i] == DIRECT_CHAR || s[i] == LABEL_CHAR)
		i++;
	if (s[i] == LABEL_CHAR || s[i] == '+' || s[i] == '-')
		i++;
	while (ft_strchr(LABEL_CHARS, s[i]) || s[i] == LABEL_CHAR)
		if (!s[i] || s[i++] == LABEL_CHAR)
			break ;
	return (ft_strndup(s, i));
}
