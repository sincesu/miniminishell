/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_command_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 03:17:08 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:22:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

static int	ft_is_direct_path(char *cmd)
{
	return (cmd && (ft_strncmp(cmd, "/", 1) == 0
			|| ft_strncmp(cmd, "./", 2) == 0));
}

static char	*ft_path_join(char *path, char *command)
{
	int		len;
	char	*result;

	len = ft_strlen(path) + 1 + ft_strlen(command) + 1;
	result = ft_alloc(sizeof(char) * len);
	ft_strlcpy(result, path, len);
	ft_strlcat(result, "/", len);
	ft_strlcat(result, command, len);
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
		full_path = ft_path_join(paths[i], command);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}
