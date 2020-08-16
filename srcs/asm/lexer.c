/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:22:33 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/03 16:34:23 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	reverse_tokens(t_tok **token)
{
	t_tok	*prev;
	t_tok	*curr;
	t_tok	*next;

	prev = NULL;
	curr = *token;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*token = prev;
}

static int	get_token_col(char *buf, char *s)
{
	int	col;
	int	n;
	int	i;

	col = 1;
	n = ft_strlen(buf) - ft_strlen(s);
	i = -1;
	while (++i < n && col++)
		if (buf[i] == '\n')
			col = 1;
	return (col);
}

static int	get_token_row(char *buf, char *s)
{
	int	row;
	int	n;
	int	i;

	row = 1;
	n = ft_strlen(buf) - ft_strlen(s);
	i = -1;
	while (++i < n)
		if (buf[i] == '\n')
			row++;
	return (row);
}

static void	add_new_token(t_exec *info, char *s)
{
	t_tok	*new;

	if (!(new = (t_tok *)ft_memalloc(sizeof(t_tok))))
		terminate(info, 0, NULL);
	new->row = get_token_row(info->buf, s);
	new->col = get_token_col(info->buf, s);
	new->next = info->token;
	info->token = new;
	lexical_check(info, s);
	if (*s && !(new->content = get_token_content(s)))
		terminate(info, 0, NULL);
	new->type = get_token_type(new->content);
}

void		lex_corewar(t_exec *info)
{
	int	i;

	i = 0;
	add_new_token(info, info->buf);
	while (info->token->type != END)
	{
		i += ft_strlen(info->token->content);
		add_new_token(info, &info->buf[i]);
	}
	reverse_tokens(&info->token);
	strip_tokens(info);
	syntax_check(info);
}
