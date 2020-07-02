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

static char	*get_other(char *s)
{
	int	i;

	i = 0;
	if (ft_strchr(LABEL_CHARS, *s) || *s == LABEL_CHAR || (*s == DIRECT_CHAR &&
	*(s + 1) == LABEL_CHAR))
	{
		if (*s == DIRECT_CHAR && (*(s + 1) == LABEL_CHAR))
			i += 2;
		else if (*s == LABEL_CHAR)
			i += 1;
		while (s[i] && ft_strchr(LABEL_CHARS, s[i]))
			i++;
		if (s[i] == LABEL_CHAR)
			i++;
	}
	else
	{
		if (*s == DIRECT_CHAR && *(s + 1) == '-')
			i += 2;
		else if (*s == '-' || *s == DIRECT_CHAR)
			i += 1;
		while (ft_isdigit(s[i]))
			i++;
	}
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

static char	*get_comment(char *s)
{
	int	i;

	i = 0;
	while (s[++i])
		if (s[i] == '\n')
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

char		*get_token_content(char *s)
{
	if (!ft_strncmp(s, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		return (ft_strdup(NAME_CMD_STRING));
	if (!ft_strncmp(s, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		return (ft_strdup(COMMENT_CMD_STRING));
	if (*s == STRING_CHAR)
		return (get_string(s));
	if (*s == SEPARATOR_CHAR || *s == '\n')
		return (ft_strndup(s, sizeof(*s)));
	if (*s == COMMENT_CHAR || *s == COMMENT_CHAR_2)
		return (get_comment(s));
	if (ft_isspace(*s))
		return (get_whitespace(s));
	return (get_other(s));
}
