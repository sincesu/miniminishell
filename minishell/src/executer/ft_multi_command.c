/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:53:23 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/09 01:51:33 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/wait.h>
#include <unistd.h>

static void	ft_execute_pipeline_command(t_shell *shell, t_parser *parsed,
	int **pipes)
{
	int	cmd_count;

	cmd_count = ft_count_commands(parsed);
	init_command_redirections(parsed, pipes, cmd_count);
	ft_close_all_pipes(pipes, cmd_count - 1);
	ft_safe_close_fds(parsed);
	if (ft_is_builtin(parsed->args[0]))
		safe_abort(ft_execute_builtin(shell, parsed));
	else
		safe_abort(ft_shell_command(shell, parsed));
}

static t_parser	*ft_prepare_child_command(t_parser *cmds, int i,
	int **pipes, int cmd_count)
{
	t_parser	*target;
	int			j;
	int			k;

	j = 0;
	k = 0;
	while (j < cmd_count - 1)
	{
		if (j != i - 1)
			close(pipes[j][0]);
		if (j != i)
			close(pipes[j][1]);
		j++;
	}
	target = cmds;
	while (k < i && target)
	{
		target = target->next;
		k++;
	}
	return (target);
}

static void	ft_child_process(t_shell *shell, t_parser *parsed,
	int **pipes, int i)
{
	t_parser	*target;
	int			cmd_count;

	cmd_count = ft_count_commands(parsed);
	ft_init_signals(EXECUTION);
	target = ft_prepare_child_command(parsed, i, pipes, cmd_count);
	if (!target)
	{
		ft_close_all_pipes(pipes, cmd_count - 1);
		safe_abort(1);
	}
	target->fd_in = STDIN_FILENO;
	target->fd_out = STDOUT_FILENO;
	if (i > 0)
		target->fd_in = pipes[i - 1][0];
	if (i < cmd_count - 1)
		target->fd_out = pipes[i][1];
	ft_execute_pipeline_command(shell, target, pipes);
}

static int	ft_wait_for_pipeline(pid_t *pids, int cmd_count)
{
	int	status;
	int	last_exit_code;
	int	i;

	last_exit_code = 0;
	i = 0;
	while (i < cmd_count)
	{
		if (pids[i] > 0)
		{
			waitpid(pids[i], &status, 0);
			if (i == cmd_count - 1)
				last_exit_code = WEXITSTATUS(status);
		}
		i++;
	}
	ft_init_signals(PROMPT);
	return (last_exit_code);
}

int	ft_multi_command(t_shell *shell, t_parser *parsed)
{
	int			cmd_count;
	pid_t		*pids;
	int			**pipes;
	int			i;

	cmd_count = ft_count_commands(parsed);
	pids = ft_alloc(sizeof(pid_t) * cmd_count);
	pipes = ft_alloc(sizeof(int *) * (cmd_count - 1));
	if (ft_create_pipes(pipes, cmd_count - 1))
		return (1);
	i = 0;
	while (i < cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (ft_cleanup_failed_fork(pids, i,
					pipes, cmd_count - 1));
		if (pids[i] == 0)
			ft_child_process(shell, parsed, pipes, i);
		i++;
	}
	ft_init_signals(IGNORE);
	ft_close_all_pipes(pipes, cmd_count - 1);
	return (ft_wait_for_pipeline(pids, cmd_count));
}
