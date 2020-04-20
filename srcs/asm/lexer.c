/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:22:33 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/03 16:34:23 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_type	get_type(char **data, char *content, size_t i, size_t j)
{
	if (!data[j])
		return (END);
	if (!data[j][i])
		return (ENDLINE);
	if (!ft_strcmp(content, NAME_CMD_STRING))
		return (COMMAND_NAME);
	if (!ft_strcmp(content, COMMENT_CMD_STRING))
		return (COMMAND_COMMENT);
	//if (*content == COMMAND_CHAR)
	//	return (COMMAND);
	if (*content == SEPARATOR_CHAR)
		return (SEPARATOR);
	if (*content == STRING_CHAR)
		return (STRING);
	if (*content == LABEL_CHAR)
		return (INDIRECT_LABEL);
	if (*content == DIRECT_CHAR)
		return (*(content + 1) == LABEL_CHAR ? DIRECT_LABEL : DIRECT);
	if (content[ft_strlen(content) - 1] == LABEL_CHAR)
		return (LABEL);
	if (ft_isdigit(*content) || *content == '+' || *content == '-')
		return (INDIRECT);
	if (*content == REG_CHAR)
		return (REGISTER);
	return (INSTRUCTION);
}

static char		*get_string(t_asm *info, char **data, size_t *i, size_t *j)
{
	char	*str;
	size_t	len;

	len = 0;
	if (!(str = (char *)malloc(sizeof(char) * (++len + 1))))
		terminate(info, 0, NULL);
	str[0] = data[(*j)--][*i];
	str[len] = '\0';
	while (data[++(*j)])
	{
		while (!ft_strchr(&str[1], STRING_CHAR))
		{
			if (!(str = (char *)ft_reallocf(str, sizeof(char) * (++len + 1))))
				terminate(info, 0, NULL);
			str[len] = '\0';
			if (data[*j][*i + 1])
				str[len - 1] = data[*j][++(*i)];
			else if ((str[len - 1] = '\n'))
				break ;
		}
		if (!data[*j + 1] || ft_strchr(&str[1], STRING_CHAR))
			break ;
		*i = -1;
	}
	return (str);
}

static char		*get_content(t_asm *info, char **data, size_t *i, size_t *j)
{
	char	*str;
	size_t	start;

	if (!data[*j] || !data[*j][*i])
		return (NULL);
	if (data[*j][*i] == STRING_CHAR)
		return (get_string(info, data, i, j));
	start = *i;
	if (data[*j][*i] == DIRECT_CHAR && data[*j][*i + 1] == LABEL_CHAR)
		(*i)++;
	if (data[*j][*i] != SEPARATOR_CHAR)
		while (data[*j][*i + 1] && !ft_isspace(data[*j][*i + 1]) &&
		data[*j][*i + 1] != COMMAND_CHAR && data[*j][*i + 1] != STRING_CHAR &&
		data[*j][*i + 1] != DIRECT_CHAR && data[*j][*i + 1] != SEPARATOR_CHAR)
			if (data[*j][(*i)++ + 1] == LABEL_CHAR)
				break ;
	if (!(str = ft_strsub(data[*j], start, *i - start + 1)))
		terminate(info, 0, NULL); // memory error
	return (str);
}

static void		add_new_token(t_asm *info, size_t *i, size_t *j)
{
	t_token	*new;

	if (!(new = (t_token *)ft_memalloc(sizeof(t_token))))
		terminate(info, 0, NULL);
	new->next = info->token;
	info->token = new;
	new->col = *i;
	new->row = *j;
	new->content = get_content(info, info->data, i, j);
	new->type = get_type(info->data, new->content, new->col, new->row);
	//lexical_check(info);
}

void			tokenize_data(t_asm *info)
{
	size_t	i;
	size_t	j;

	j = -1;
	while (info->data[++j])
	{
		i = -1;
		while (info->data[j][++i])
		{
			if (ft_isspace(info->data[j][i]))
				continue ;
			add_new_token(info, &i, &j);
		}
		add_new_token(info, &i, &j);
	}
	add_new_token(info, &i, &j);
	syntax_check(info);
}
