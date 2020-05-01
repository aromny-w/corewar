/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 21:54:00 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/01 20:22:07 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_header_error(int status)
{
	if (status == 9)
		ft_dprintf(2, "Champion name too long (Max length %d)\n", NAME_MAX);
	else if (status == 10)
		ft_dprintf(2, "Champion comment too long (Max length %d)\n",
		COMMENT_LENGTH);
}

static void	print_syntax_error(int status, t_token *token)
{
	if (status == 3)
		ft_dprintf(2, "Syntax error - unexpected end of input (Perhaps you forg\
ot to end with a newline ?)\n");
	else if (status == 4)
		ft_dprintf(2, "Syntax error at token ");
	else if (status == 5)
		ft_dprintf(2, "Invalid instruction at token ");
	else if (status == 6)
		ft_dprintf(2, "Invalid parameter %d type %s for instruction %s\n", 0, NULL);
	else if (status == 7)
		ft_dprintf(2, "Invalid parameter count for instruction %s\n", NULL);
	else if (status == 8)
		ft_dprintf(2, "No such label %s while attempting to dereference token ", NULL);
	if (status == 4 || status == 5 || status == 8)
	{
		if (token->type != ENDLINE && token->type != END)
			ft_dprintf(2, "[TOKEN][%03d:%03d] %s \"%s\"\n", token->row, token->col, g_op_tab[token->type], token->content);
		else
			ft_dprintf(2, "[TOKEN][%03d:%03d] %s\n");
	}
}

static void	print_lexical_error(int status, t_token *token)
{
	if (status == 2)
		ft_dprintf(2, "Lexical error at [%d:%d]\n", token->row, token->col);
}

static void	print_error(t_prog *info, int status, t_token *token)
{
	if (status == 0)
		ft_dprintf(2, "%s\n", strerror(errno));
	else if (status == 1)
		ft_dprintf(2, "Can't read source file %s.\n", info->path);
	else if (status == 2)
		print_lexical_error(status, token);
	else if (status >= 3 && status <= 8)
		print_syntax_error(status, token);
	else if (status == 9 || status == 10)
		print_header_error(status);
}

void		terminate(t_prog *info, int status, t_token *token)
{
	print_error(info, status, token);
	destroy_struct(info);
	exit(EXIT_FAILURE);
}
