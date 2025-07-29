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

static int	ft_handle_redirections(t_parser *parsed,
	int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (ft_apply_redirections(parsed->redirect,
			parsed->redirect_count, 0) == -1)
	{
		ft_restore_std_fds(*saved_stdin, *saved_stdout);
		return (-1);
	}
	return (0);
}

int	ft_prepare_heredocs(t_shell *shell, t_parser *parsed)
{
	t_redirect	*redir;
	int			flag;
	int			i;

	redir = parsed->redirect;
	if (!redir)
		return (0);
	i = 0;
	while (i < parsed->redirect_count)
	{
		flag = 0;
		if (redir[i].flags == S_WORD || redir[i].flags == D_WORD)
			flag = 1;
		if (redir[i].type == R_HERE && !redir[i].document)
			redir[i].document = ft_get_heredoc_input(redir[i].file_name,
					shell, flag);
		i++;
	}
	return (0);
}

int	ft_one_command(t_shell *shell, t_parser *parsed)
{
	int			exit_code;
	int			saved_stdin;
	int			saved_stdout;

	ft_prepare_heredocs(shell, parsed);
	saved_stdin = -1;
	saved_stdout = -1;
	if (ft_handle_redirections(parsed,
			&saved_stdin, &saved_stdout) == -1)
		return (1);
	if (!parsed->args || !parsed->args[0])
	{
		ft_restore_std_fds(saved_stdin, saved_stdout);
		return (0);
	}
	if (ft_is_builtin(parsed->args[0]))
		exit_code = ft_execute_builtin(shell, parsed);
	else
		exit_code = ft_shell_command(shell, parsed);
	ft_restore_std_fds(saved_stdin, saved_stdout);
	return (exit_code);
}
