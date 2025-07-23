/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:53:23 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:22:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

pid_t	create_child_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

void	execute_pipeline_command(t_shell *shell, t_parser *parser,
			int input_fd, int output_fd)
{
	int		exit_code;
	char	*full_path;

	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			exit(1);
		}
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			exit(1);
		}
		close(output_fd);
	}
	if (parser->redirect && ft_apply_redirections(parser->redirect) == -1)
		exit(1);
	if (ft_is_builtin(parser->args[0]))
	{
		exit_code = ft_execute_builtin(shell, parser);
		exit(exit_code);
	}
	else
	{
		full_path = ft_search_command_path(parser->args[0]);
		if (!full_path)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(parser->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		execve(full_path, parser->args, shell->env);
		perror("execve");
		exit(126);
	}
}

t_token	*create_command_tokens(t_token *start, t_token *end)
{
	t_token	*head;
	t_token	*tail;
	t_token	*current;
	t_token	*new_token;

	head = NULL;
	tail = NULL;
	current = start;
	while (current && current != end)
	{
		new_token = ft_alloc(sizeof(t_token));
		new_token->content = ft_strdup(current->content);
		new_token->type = current->type;
		new_token->flag = current->flag;
		new_token->next = NULL;
		new_token->prev = tail;
		if (!head)
			head = new_token;
		else
			tail->next = new_token;
		tail = new_token;
		current = current->next;
	}
	return (head);
}

t_parser	*parse_pipeline_commands(t_shell *shell, int *cmd_count)
{
	t_token		*current;
	int			count;
	t_parser	*commands;
	int			cmd_index;
	t_token		*cmd_start;
	t_token		*cmd_end;
	t_token		*cmd_tokens;
	t_shell		temp_shell;
	t_parser	temp_parsed;

	current = shell->args;
	count = 1;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	*cmd_count = count;
	commands = ft_alloc(sizeof(t_parser) * count);
	current = shell->args;
	cmd_index = 0;
	cmd_start = current;
	while (current && cmd_index < count)
	{
		if (current->type == PIPE || current->next == NULL)
		{
			if (current->type == PIPE)
				cmd_end = current;
			else
				cmd_end = current->next;
			cmd_tokens = create_command_tokens(cmd_start, cmd_end);
			temp_shell = *shell;
			temp_shell.args = cmd_tokens;
			ft_bzero(&temp_parsed, sizeof(t_parser));
			commands[cmd_index] = ft_parse_command(&temp_shell, temp_parsed);
			if (cmd_index > 0)
			{
				commands[cmd_index].prev = &commands[cmd_index - 1];
				commands[cmd_index - 1].next = &commands[cmd_index];
			}
			if (cmd_index == 0)
				commands[cmd_index].prev = NULL;
			cmd_index++;
			if (current->next)
				cmd_start = current->next;
		}
		current = current->next;
	}
	if (count > 0)
		commands[count - 1].next = NULL;
	return (commands);
}

int	wait_for_pipeline(pid_t *pids, int cmd_count)
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
	return (last_exit_code);
}

int	ft_multi_command(t_shell *shell, t_parser *parsed)
{
	int			cmd_count;
	int			exit_code;
	t_parser	*commands;
	pid_t		*pids;
	int			**pipes;
	int			i;
	int			j;
	int			input_fd;
	int			output_fd;

	(void)parsed;
	commands = parse_pipeline_commands(shell, &cmd_count);
	if (!commands || cmd_count == 0)
		return (1);
	pids = ft_alloc(sizeof(pid_t) * cmd_count);
	pipes = ft_alloc(sizeof(int *) * (cmd_count - 1));
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = ft_alloc(sizeof(int) * 2);
		if (create_pipe(pipes[i]) == -1)
			return (1);
		i++;
	}
	i = 0;
	while (i < cmd_count)
	{
		pids[i] = create_child_process();
		if (pids[i] == -1)
		{
			j = 0;
			while (j < cmd_count - 1)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			return (1);
		}
		if (pids[i] == 0)
		{
			input_fd = STDIN_FILENO;
			output_fd = STDOUT_FILENO;
			if (i > 0)
				input_fd = pipes[i - 1][0];
			if (i < cmd_count - 1)
				output_fd = pipes[i][1];
			j = 0;
			while (j < cmd_count - 1)
			{
				if (j != i - 1 || i == 0)
					close(pipes[j][0]);
				if (j != i || i == cmd_count - 1)
					close(pipes[j][1]);
				j++;
			}
			execute_pipeline_command(shell, &commands[i], input_fd, output_fd);
		}
		i++;
	}
	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	exit_code = wait_for_pipeline(pids, cmd_count);
	return (exit_code);
}
