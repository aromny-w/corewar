/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 21:17:03 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/05 21:17:04 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	reverse_lines(t_line **line)
{
	t_line	*prev;
	t_line	*curr;
	t_line	*next;

	prev = NULL;
	curr = *line;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*line = prev;
}

static t_op	get_operation(t_exec *info, t_token *token)
{
	int	i;

	i = -1;
	while (g_op_tab[++i].name)
		if (!ft_strcmp(token->content, g_op_tab[i].name))
			break ;
	if (!g_op_tab[i].name)
		terminate(info, 5, token);
	return (g_op_tab[i]);
}

static void	add_new_line(t_exec *info, t_token **token)
{
	t_line	*new;
	int		i;

	if (!(new = (t_line *)ft_memalloc(sizeof(t_line))))
		terminate(info, 0, NULL);
	new->next = info->line;
	info->line = new;
	if ((*token)->type == LABEL && (new->label = *token))
		*token = (*token)->next;
	if ((*token)->type == INSTRUCTION)
		new->op = get_operation(info, *token);
	i = -1;
	while ((*token)->type != ENDLINE)
	{
		*token = (*token)->next;
		if (++i < MAX_ARGS_NUMBER)
			new->arg[i].token = *token;
		*token = (*token)->next;
	}
}

static void	set_header(t_exec *info, t_token **token)
{
	char	*s1;
	char	*s2;
	size_t	len1;
	size_t	len2;

	s1 = NULL;
	s2 = NULL;
	while (!s1 || !s2)
	{
		while ((*token)->type == ENDLINE)
			*token = (*token)->next;
		if ((*token)->type == COMMAND_NAME)
			s1 = (*token)->next->content + 1;
		if ((*token)->type == COMMAND_COMMENT)
			s2 = (*token)->next->content + 1;
		*token = (*token)->next->next;
	}
	if ((len1 = ft_strlen(s1) - 1) > PROG_NAME_LENGTH)
		terminate(info, 9, NULL);
	if ((len2 = ft_strlen(s2) - 1) > COMMENT_LENGTH)
		terminate(info, 10, NULL);
	ft_strncpy(info->header.prog_name, s1, len1);
	ft_strncpy(info->header.comment, s2, len2);
}

void		parse_tokens(t_exec *info)
{
	t_token	*tptr;

	tptr = info->token;
	set_header(info, &tptr);
	while ((tptr = tptr->next)->type != END)
		add_new_line(info, &tptr);
	reverse_lines(&info->line);
}
