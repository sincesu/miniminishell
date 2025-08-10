/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 03:17:11 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/10 23:57:20 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
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

void	check_command_errors(char *path, t_parser *parsed)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_perror(parsed->args[0], NULL, "Is a directory");
		ft_safe_close_fds(parsed);
		safe_abort(126);
	}
	if (ft_strchr(parsed->args[0], '/') && access(path, F_OK) != 0)
	{
		ft_perror(parsed->args[0], NULL, "No such file or directory");
		ft_safe_close_fds(parsed);
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

static char	*ft_get_basename(char *path)
{
	char	*last_slash;

	last_slash = ft_strrchr(path, '/');
	if (last_slash)
		return (last_slash + 1);
	return (path);
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
		ft_perror("fork", NULL, NULL);
		return (1);
	}
	else if (pid == 0)
		ft_execute_external_command(full_path, parsed, shell->env);
	if (ft_strncmp(ft_get_basename(parsed->args[0]), "minishell", 10) == 0)
		ft_init_signals(IGNORE);
	return (ft_wait_child_process(pid));
}
