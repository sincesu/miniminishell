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

char	*ft_get_env_value(const char *name)
{
	extern char **environ;
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
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
	result = ft_calloc(total_len + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < count)
		ft_strlcat(result, arr[i++], total_len + 1);
	return (result);
}

void	ft_free_split(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	**ft_get_env_to_array(void)
{
	extern char **environ;
	int		count;
	int		i;
	char	**copy;

	count = 0;
	while (environ[count])
		count++;
	copy = ft_calloc(count + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(environ[i]);
		i++;
	}
	return (copy);
}

char	*ft_search_command_path(char *command)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	if (ft_is_direct_path(command))
		return (ft_strdup(command));
	path_env = ft_get_env_value("PATH");
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
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

int	ft_shell_commands(t_shell *shell)
{
	char	**argv;
	char	**envp;
	char	*full_path;
	pid_t	pid;
	int		status;

	if (!shell->args || !shell->args->content)
		return (0);
	full_path = ft_search_command_path(shell->args->content);
	if (!full_path)
	{
		printf("minishell: %s: command not found\n", shell->args->content);
		return (127);
	}
	argv = token_list_to_argv(shell->args);
	envp = ft_get_env_to_array();
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		execve(full_path, argv, envp);
		perror("execve");
		exit(126);
	}
	else
	{
		waitpid(pid, &status, 0);
		shell->exit_code = WEXITSTATUS(status);
	}
	ft_free_split(argv);
	ft_free_split(envp);
	free(full_path);
	return (shell->exit_code);
}