/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 03:17:11 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:22:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

static char	*ft_get_executable_path(char *command)
{
	char	*full_path;

	full_path = ft_search_command_path(command);
	if (full_path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (full_path);
}

static void	ft_execute_external_command(char *path, char **args, char **env)
{
	ft_init_signals(EXECUTION);
	execve(path, args, env);
	perror("execve");
	exit(126);
}

static int	ft_wait_child_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	ft_init_signals(PROMPT);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	ft_shell_command(t_shell *shell, t_parser *parser)
{
	pid_t	pid;
	char	*full_path;

	full_path = ft_get_executable_path(parser->args[0]);
	if (full_path == NULL)
		return (127);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
		ft_execute_external_command(full_path, parser->args, shell->env);
	printf("%s\n", parser->args[0]);
	if (ft_strncmp(parser->args[0], "./minishell", sizeof("./minishell") == 0))
		ft_init_signals(IGNORE);
	return (ft_wait_child_process(pid));
}
