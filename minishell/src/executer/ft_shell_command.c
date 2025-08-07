/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 03:17:11 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/06 21:14:05 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

static char	*ft_get_executable_path(char *command)
{
	char	*full_path;

	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	full_path = ft_search_command_path(command);
	if (full_path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		if (command[0])
			ft_putstr_fd(command, 2);
		else
			ft_putstr_fd("\"\"", 2);
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

void	check_command_errors(char *path, t_parser *parsed)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(parsed->args[0], 2);
		ft_putendl_fd(": Is a directory", 2);
		if (parsed->fd_in != STDIN_FILENO)
			close(parsed->fd_in);
		if (parsed->fd_out != STDOUT_FILENO)
			close(parsed->fd_out);
		safe_abort(126);
	}
	if (ft_strchr(parsed->args[0], '/') && access(path, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(parsed->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		if (parsed->fd_in != STDIN_FILENO)
			close(parsed->fd_in);
		if (parsed->fd_out != STDOUT_FILENO)
			close(parsed->fd_out);
		safe_abort(127);
	}
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

int	ft_shell_command(t_shell *shell, t_parser *parsed)
{
	pid_t	pid;
	char	*full_path;

	full_path = ft_get_executable_path(parsed->args[0]);
	if (full_path == NULL)
		return (127);
	ft_init_signals(EXECUTION);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
		ft_execute_external_command(full_path, parsed, shell->env);
	if (ft_strncmp("./minishell", parsed->args[0],
			ft_strlen("./minishell") + 1) == 0)
		ft_init_signals(IGNORE);
	return (ft_wait_child_process(pid));
}
