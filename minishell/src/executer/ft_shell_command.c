/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 03:17:11 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/01 19:27:08 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

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

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

#include <sys/stat.h> // stat için
#include <unistd.h>   // access
#include <errno.h>    // errno

static void	ft_execute_external_command(char *path, char **args, char **env)
{
	struct stat	st;

	ft_init_signals(EXECUTION);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": Is a directory", 2);
		safe_abort(126);
	}
	if ((args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/'))
		&& access(path, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		safe_abort(127);
	}
	execve(path, args, env);
	perror("execve");
	safe_abort(126);
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
	if (ft_strncmp(parser->args[0], "./minishell", sizeof("./minishell") == 0))
		ft_init_signals(IGNORE);
	return (ft_wait_child_process(pid));
}
