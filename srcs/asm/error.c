/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 03:55:26 by aromny-w          #+#    #+#             */
/*   Updated: 2020/05/11 03:55:28 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_token_type_str(t_type type)
{
	if (type == COMMAND_NAME)
		return ("COMMAND_NAME");
	if (type == COMMAND_COMMENT)
		return ("COMMAND_COMMENT");
	if (type == STRING)
		return ("STRING");
	if (type == LABEL)
		return ("LABEL");
	if (type == INSTRUCTION)
		return ("INSTRUCTION");
	if (type == REGISTER)
		return ("REGISTER");
	if (type == DIRECT)
		return ("DIRECT");
	if (type == DIRECT_LABEL)
		return ("DIRECT_LABEL");
	if (type == INDIRECT)
		return ("INDIRECT");
	if (type == INDIRECT_LABEL)
		return ("INDIRECT_LABEL");
	if (type == ENDLINE)
		return ("ENDLINE");
	if (type == SEPARATOR)
		return ("SEPARATOR");
	return ("END");
}

static char	*get_param_type_str(t_arg_type type)
{
	if (type == T_REG)
		return ("register");
	if (type == T_DIR)
		return ("direct");
	if (type == T_IND)
		return ("indirect");
	return (NULL);
}

static void	print_syntax_error(int status, t_token *token, t_line *line, int n)
{
	if (status == 3)
		ft_dprintf(2, "Syntax error - unexpected end of input (Perhaps you forg\
ot to end with a newline ?)\n");
	else if (status == 4)
		ft_dprintf(2, "Syntax error at token ");
	else if (status == 5)
		ft_dprintf(2, "Invalid instruction at token ");
	else if (status == 6 || status > 10)
		ft_dprintf(2, "Invalid parameter %d type %s for instruction %s\n",
		n, get_param_type_str(line->arg[n].type), line->op.name);
	else if (status == 7)
		ft_dprintf(2, "Invalid parameter count for instruction %s\n",
		line->op.name);
	else if (status == 8)
		ft_dprintf(2, "No such label %s while attempting to dereference token ",
		token->type == DIRECT_LABEL ? token->content + 2 : token->content + 1);
	if (status == 4 || status == 5 || status == 8)
	{
		if (token->type != ENDLINE)
			ft_dprintf(2, "[TOKEN][%03d:%03d] %s \"%s\"\n", token->row,
			token->col, get_token_type_str(token->type), token->content);
		else
			ft_dprintf(2, "[TOKEN][%03d:%03d] %s\n", token->row, token->col,
			get_token_type_str(token->type));
	}
}

static void	print_lexical_error(int status, t_token *token)
{
	if (status == 2)
		ft_dprintf(2, "Lexical error at [%d:%d]\n", token->row, token->col);
}

void		print_error(t_prog *info, int status, void *ptr)
{
	if (status == 0)
		ft_dprintf(2, "%s\n", strerror(errno));
	else if (status == 1)
		ft_dprintf(2, "Can't read source file %s\n", info->path);
	else if (status == 2)
		print_lexical_error(status, ptr);
	else if ((status >= 3 && status <= 8) || status > 10)
		print_syntax_error(status, ptr, ptr, status - 11);
	else if (status == 9)
		ft_dprintf(2, "Champion name too long (Max length %d)\n",
		PROG_NAME_LENGTH);
	else if (status == 10)
		ft_dprintf(2, "Champion comment too long (Max length %d)\n",
		COMMENT_LENGTH);
}
