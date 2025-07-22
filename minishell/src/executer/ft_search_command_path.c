#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

static int	ft_is_direct_path(char *cmd)
{
	return (cmd && (ft_strncmp(cmd, "/", 1) == 0
			|| ft_strncmp(cmd, "./", 2) == 0));
}

static char	*ft_str_arr_join(char **arr, int count)
{
	int		total_len;
	char	*result;
	int		i;

	if (arr == NULL || *arr == NULL || count == 0)
		return (NULL);
	total_len = 0;
	i = 0;
	while (i < count)
		total_len += ft_strlen(arr[i++]);
	result = ft_alloc(sizeof(char) * (total_len + 1));
	result[0] = '\0';
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
	if (path_env == NULL)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		full_path = ft_str_arr_join((char *[]){paths[i], "/", command}, 3);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}
