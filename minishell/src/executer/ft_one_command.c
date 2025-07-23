/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 03:16:44 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:22:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

static void	ft_restore_std_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

static int	ft_handle_redirections(t_redirect *redir,
	int *saved_stdin, int *saved_stdout)
{
	if (!redir)
		return (0);
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (ft_apply_redirections(redir) == -1)
	{
		ft_restore_std_fds(*saved_stdin, *saved_stdout);
		return (-1);
	}
	return (0);
}

static int	ft_prepare_heredocs(t_shell *shell, t_parser *parsed)
{
	t_redirect	*redir;

	redir = parsed->redirect;
	while (redir)
	{
		if (redir->type == R_HERE && !redir->document)
			redir->document = ft_get_heredoc_input(redir->file_name,
					shell);
		redir = redir->next;
	}
	return (0);
}

int	ft_one_command(t_shell *shell, t_parser *parsed)
{
	int			exit_code;
	int			saved_stdin;
	int			saved_stdout;
	t_parser	new_parsed;

	new_parsed = ft_parse_command(shell, *parsed);
	ft_prepare_heredocs(shell, &new_parsed);
	saved_stdin = -1;
	saved_stdout = -1;
	if (ft_handle_redirections(new_parsed.redirect,
			&saved_stdin, &saved_stdout) == -1)
		return (1);
	if (!new_parsed.args || !new_parsed.args[0])
	{
		ft_restore_std_fds(saved_stdin, saved_stdout);
		return (0);
	}
	if (ft_is_builtin(new_parsed.args[0]))
		exit_code = ft_execute_builtin(shell, &new_parsed);
	else
		exit_code = ft_shell_command(shell, &new_parsed);
	ft_restore_std_fds(saved_stdin, saved_stdout);
	return (exit_code);
}
