#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	ft_is_direct_path(char *cmd)
{
	return (cmd && (ft_strncmp(cmd, "/", 1) == 0 || ft_strncmp(cmd, "./", 2) == 0));
}

char	*str_arr_join(char **arr, int count)
{
	int		total_len;
	char	*result;
	int		i;

	total_len = 0;
    i = 0; 
	while (i < count)
		total_len += ft_strlen(arr[i++]);
	result = ft_alloc(total_len + 1 * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < count)
		ft_strlcat(result, arr[i++], total_len + 1);
	return (result);
}

char	*ft_search_command_path(char *command)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	if (ft_is_direct_path(command))
		return (ft_strdup(command));
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = str_arr_join((char *[]){paths[i], "/", command}, 3);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

int	ft_shell_command(t_shell *shell, t_exec_unit *parsed)
{
	char	*full_path;
	pid_t	pid;
	int		status;

	if (!shell->args || !shell->args->content)
		return (0);
	full_path = ft_search_command_path(shell->args->content);
	if (!full_path)
	{
		printf("minishell: %s: command not found\n", parsed->args[0]);
		shell->exit_code = 127;
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		execve(full_path, parsed->args, shell->env);
		perror("execve");
		exit(126);
	}
	else
	{
		waitpid(pid, &status, 0);
		shell->exit_code = WEXITSTATUS(status);
	}
	//free(full_path);
	return (shell->exit_code);
}