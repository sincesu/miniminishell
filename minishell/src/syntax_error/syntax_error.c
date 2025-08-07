/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:41:09 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/07 19:00:29 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdio.h>

static int	r_append_error(t_token *a, t_shell *shell)
{
	if (a->type == R_APPEND)
	{
		if (!a->next)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token"
				" 'newline'\n", 2);
			shell->exit_code = 2;
			return (1);
		}
		if (is_operator(a->next->content[0]))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token"
				"`>>'\n", 2);
			shell->exit_code = 2;
			return (1);
		}
	}
	return (0);
}

static int	r_here_error(t_token *a, t_shell *shell)
{
	if (!a->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token"
			" 'newline'\n", 2);
		shell->exit_code = 2;
		return (1);
	}
	if (is_operator(a->next->content[0]))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
		shell->exit_code = 2;
		return (1);
	}
	return (0);
}

static int	r_in_and_r_out_error(t_token *a, t_shell *shell)
{
	if (!a->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token"
			" 'newline'\n", 2);
		shell->exit_code = 2;
		return (1);
	}
	return (0);
}

static int	pipe_error(char *str, t_token *a, t_shell *shell)
{
	if (!a->next)
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
		shell->exit_code = 2;
		return (1);
	}
	if (is_operator(str[0]))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		shell->exit_code = 2;
		return (1);
	}
	else if (a->next->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		shell->exit_code = 2;
		return (1);
	}
	return (0);
}

int	syntax_error(t_shell *shell)
{
	t_token	*token;
	char	*str;

	token = shell->args;
	while (token && token->content)
	{
		if (is_operator(token->content[0]))
		{
			if (token->type == R_APPEND)
				if (r_append_error(token, shell))
					return (1);
			if (token->type == R_HERE)
				if (r_here_error(token, shell))
					return (1);
			if (token->type == R_OUT || token->type == R_IN)
				if (r_in_and_r_out_error(token, shell))
					return (1);
			if (token->type == PIPE)
				if (pipe_error(str, token, shell))
					return (1);
		}
		str = token->content;
		token = token->next;
	}
	return (0);
}
