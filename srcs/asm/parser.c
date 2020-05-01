/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 21:17:03 by student           #+#    #+#             */
/*   Updated: 2020/04/05 21:17:04 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_op	get_operation(t_prog *info, t_token *token)
{
	int	i;

	i = -1;
	while (g_op_tab[++i].name)
		if (!ft_strcmp(token->content, g_op_tab[i].name))
			break ;
	if (!g_op_tab[i].name)
		terminate(info, 0, token); // invalid inst
	return (g_op_tab[i]);
}

static void	add_new_instr(t_prog *info, t_token *label, t_token **token)
{
	t_instr	*new;
	int		i;

	if (!(new = (t_instr *)ft_memalloc(sizeof(t_instr))))
		terminate(info, 0, NULL); // memory error;
	new->next = info->instr;
	info->instr = new;
	if ((new->arg[3].token = label) && (*token = (*token)->next) &&
	(!(new->label = ft_strndup(label->content, ft_strlen(label->content) - 1))))
		terminate(info, 0, NULL);
	if ((*token)->type == INSTRUCTION)
		new->op = get_operation(info, *token);
	i = -1;
	while (++i < new->op.params && (*token = (*token)->next)->type != ENDLINE)
	{
		new->arg[i].token = *token;
		*token = (*token)->next;
	}
	if (i < new->op.params || (*token)->type != ENDLINE)
		terminate(info, 0, *token); // invalid arguments
}

static void	set_header(t_prog *info, t_token **token)
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
		terminate(info, 0, NULL); // name too long
	if ((len2 = ft_strlen(s2) - 1) > COMMENT_LENGTH)
		terminate(info, 0, NULL); // comment too long
	ft_strncpy(info->header.prog_name, s1, len1);
	ft_strncpy(info->header.comment, s2, len2);
}

void		parse_tokens(t_prog *info)
{
	t_token	*token_ptr;

	token_ptr = info->token;
	info->header.magic = COREWAR_EXEC_MAGIC;
	set_header(info, &token_ptr);
	while ((token_ptr = token_ptr->next)->type != END)
	{
		if (token_ptr->type == ENDLINE)
			continue ;
		if (token_ptr->type == INSTRUCTION)
			add_new_instr(info, NULL, &token_ptr);
		if (token_ptr->type == LABEL)
			add_new_instr(info, token_ptr, &token_ptr);
	}
	reverse_instr(&info->instr);
	dereference_tokens(info);
}
