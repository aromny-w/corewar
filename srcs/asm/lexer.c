/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:22:33 by aromny-w          #+#    #+#             */
/*   Updated: 2020/03/26 17:39:04 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		print_tokens(t_asm *info)
{
	size_t	i;

	i = -1;
	while (info->token[++i].type != END)
	{
		if (info->token[i].type == ENDLINE)
			ft_printf("\n");
		else
			ft_printf("%s", info->token[i].content);
		if (info->token[i].type != ENDLINE &&
		info->token[i + 1].type != ENDLINE &&
		info->token[i + 1].type != END &&
		info->token[i + 1].type != SEPARATOR)
			ft_printf(" ");
	}
}

static t_type	get_type(char *content)
{
	if (!content)
		return (ENDLINE);
	if (!ft_strcmp(content, NAME_CMD_STRING))
		return (COMMAND_NAME);
	if (!ft_strcmp(content, COMMENT_CMD_STRING))
		return (COMMAND_COMMENT);
	if (*content == STRING_CHAR)
		return (STRING);
	if (content[ft_strlen(content) - 1] == LABEL_CHAR && *content != LABEL_CHAR)
		return (LABEL);
	if (*content == REG_CHAR)
		return (REGISTER);
	if (*content == DIRECT_CHAR && *(content + 1) == LABEL_CHAR)
		return (DIRECT_LABEL);
	if (*content == DIRECT_CHAR)
		return (DIRECT);
	if (*content == LABEL_CHAR)
		return (INDIRECT_LABEL);
	if (ft_isdigit(*content))
		return (INDIRECT);
	if (*content == SEPARATOR_CHAR)
		return (SEPARATOR);
	return (INSTRUCTION);
}

static char		*get_string(t_asm *info, size_t *i, size_t *j)
{
	char	*str;
	size_t	len;

	len = 0;
	if (!(str = (char *)malloc(sizeof(char) * (++len + 1))))
		terminate(info, 0);
	str[0] = info->data[(*j)--][*i];
	str[len] = '\0';
	while (info->data[++(*j)])
	{
		while (!ft_strchr(&str[1], STRING_CHAR))
		{
			if (!(str = (char *)realloc(str, sizeof(char) * (++len + 1))))
				terminate(info, 0);
			str[len] = '\0';
			if (info->data[*j][*i + 1])
				str[len - 1] = info->data[*j][++(*i)];
			else if ((str[len - 1] = '\n'))
				break ;
		}
		if (!info->data[*j + 1] || ft_strchr(&str[1], STRING_CHAR))
			break ;
		*i = -1;
	}
	return (str);
}

static char		*get_content(t_asm *info, t_token token, size_t *i, size_t *j)
{
	char	*str;

	if (!info->data[*j][*i] || info->data[*j][*i] == COMMENT_CHAR ||
	info->data[*j][*i] == COMMENT_CHAR_2)
		return (NULL);
	if (info->data[*j][*i] == STRING_CHAR)
		return (get_string(info, i, j));
	if (info->data[*j][*i + 1] == COMMAND_CHAR ||
	(info->data[*j][*i] == DIRECT_CHAR && info->data[*j][*i + 1] == LABEL_CHAR))
		(*i)++;
	if (info->data[*j][*i] != SEPARATOR_CHAR)
		while (info->data[*j][*i + 1] && !ft_isspace(info->data[*j][*i + 1]) &&
		info->data[*j][*i + 1] != COMMENT_CHAR &&
		info->data[*j][*i + 1] != COMMENT_CHAR_2 &&
		info->data[*j][*i + 1] != SEPARATOR_CHAR &&
		info->data[*j][*i + 1] != DIRECT_CHAR &&
		info->data[*j][*i + 1] != STRING_CHAR &&
		info->data[*j][*i + 1] != COMMAND_CHAR)
			if (info->data[*j][(*i)++ + 1] == LABEL_CHAR)
				break ;
	if (!(str = ft_strndup(&info->data[token.row][token.col],
	*i - token.col + 1)))
		terminate(info, 0);
	return (str);
}

static void		add_new_token(t_asm *info, size_t n, size_t *i, size_t *j)
{
	if (!(info->token = (t_token *)realloc(info->token, sizeof(t_token) *
	(n + 1))))
		terminate(info, 0);
	ft_bzero(&info->token[n], sizeof(t_token));
	info->token[n - 1].col = *i;
	info->token[n - 1].row = *j;
	info->token[n - 1].content = get_content(info, info->token[n - 1], i, j);
	info->token[n - 1].type = get_type(info->token[n - 1].content);
	//lexical_check(info, info->token[n - 1]);
}

void			tokenize_data(t_asm *info)
{
	size_t	n;
	size_t	i;
	size_t	j;

	n = 0;
	if (!(info->token = (t_token *)malloc(sizeof(t_token) * (n + 1))))
		terminate(info, 0);
	ft_bzero(&info->token[n], sizeof(t_token));
	j = -1;
	while (info->data[++j])
	{
		i = -1;
		while (info->data[j][++i])
		{
			if (ft_isspace(info->data[j][i]))
				continue ;
			if (info->data[j][i] == COMMENT_CHAR ||
			info->data[j][i] == COMMENT_CHAR_2)
				break ;
			add_new_token(info, ++n, &i, &j);
		}
		add_new_token(info, ++n, &i, &j);
	}
	syntax_check(info);
	print_tokens(info);
}
