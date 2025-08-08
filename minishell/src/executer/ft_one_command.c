/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 03:16:44 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/07 18:57:30 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

static void	ft_restore_std_fds(t_parser *parsed)
{
	if (parsed->fd_in != -1)
	{
		dup2(parsed->fd_in, STDIN_FILENO);
		close(parsed->fd_in);
	}
	if (parsed->fd_out != -1)
	{
		dup2(parsed->fd_out, STDOUT_FILENO);
		close(parsed->fd_out);
	}
}

static int	ft_handle_redirections(t_parser *parsed)
{
	parsed->fd_in = dup(STDIN_FILENO);
	parsed->fd_out = dup(STDOUT_FILENO);
	if (ft_apply_redirections(parsed->redirect,
			parsed->redirect_count, 0) == -1)
	{
		ft_restore_std_fds(parsed);
		return (-1);
	}
	return (0);
}

int	ft_one_command(t_shell *shell, t_parser *parsed)
{
	int			exit_code;

	if (ft_handle_redirections(parsed) == -1)
		return (1);
	if (ft_is_builtin(parsed->args[0]))
		exit_code = ft_execute_builtin(shell, parsed);
	else
		exit_code = ft_shell_command(shell, parsed);
	ft_restore_std_fds(parsed);
	return (exit_code);
}
