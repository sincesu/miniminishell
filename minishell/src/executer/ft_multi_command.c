/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:53:23 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/04 16:16:29 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void	ft_execute_pipeline_command(t_shell *shell, t_parser *parser,
	int input_fd, int output_fd, int **pipes)
{
	int	cmd_count;

	cmd_count = ft_count_commands(parser);
	if (input_fd != STDIN_FILENO && (dup2(input_fd, STDIN_FILENO) == -1))
	{
		ft_close_all_pipes(pipes, cmd_count - 1);
		close(input_fd);
		safe_abort(1);
	}
	if (output_fd != STDOUT_FILENO && (dup2(output_fd, STDOUT_FILENO) == -1))
	{
		ft_close_all_pipes(pipes, cmd_count - 1);
		close(output_fd);
		safe_abort(1);
	}
	if (parser->redirect && ft_apply_redirections(parser->redirect,
			parser->redirect_count, 0) == -1)
	{
		ft_close_all_pipes(pipes, cmd_count - 1);
		safe_abort(1);
	}

	if (ft_is_builtin(parser->args[0]))
	{
		ft_close_all_pipes(pipes, cmd_count - 1);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (output_fd != STDOUT_FILENO)
			close(output_fd);
		safe_abort(ft_execute_builtin(shell, parser));
	}
	else
	{
		ft_close_all_pipes(pipes, cmd_count - 1);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (output_fd != STDOUT_FILENO)
			close(output_fd);
		safe_abort((ft_shell_command(shell, parser)));
	}
}

t_parser	*ft_func(t_parser *cmds, int i, int **pipes, int cmd_count)
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

static void	ft_child_process(t_shell *shell, t_parser *cmds,
	int **pipes, int i)
{
	int			input_fd;
	int			output_fd;
	t_parser	*target;
	int			cmd_count;

	cmd_count = ft_count_commands(cmds);
	ft_init_signals(EXECUTION);
	input_fd = STDIN_FILENO;
	output_fd = STDOUT_FILENO;
	if (i > 0)
		input_fd = pipes[i - 1][0];
	if (i < ft_count_commands(cmds) - 1)
		output_fd = pipes[i][1];
	target = ft_func(cmds, i, pipes, ft_count_commands(cmds));
	if (target)
		ft_execute_pipeline_command(shell, target, input_fd, output_fd, pipes);
	else
	{
		ft_close_all_pipes(pipes, cmd_count - 1);
		safe_abort(1);
	}
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
	i = 0;
	if (cmd_count <= 0)
		return (1);
	if (ft_create_pipes(pipes, cmd_count - 1))
		return (1);
	while (i < cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (1);
		if (pids[i] == 0)
			ft_child_process(shell, parsed, pipes, i);
		i++;
	}
	ft_init_signals(IGNORE);
	ft_close_all_pipes(pipes, cmd_count - 1);
	return (ft_wait_for_pipeline(pids, cmd_count));
}
