/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:12:28 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/15 13:03:30 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../Libft/libft.h"
#include "../../include/minishell.h"

char	*find_in_env(char **env, char *name)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	find_in_env_index(char **env, char *name)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	update_env_value(char **env, int idx, char *name, char *eq)
{
	char	*new_str;
	int		len;

	len = ft_strlen(name);
	new_str = ft_alloc(len + 1 + ft_strlen(eq + 1) + 1);
	ft_strlcpy(new_str, name, len + 1);
	new_str[len] = '=';
	ft_strlcpy(new_str + len + 1, eq + 1, ft_strlen(eq + 1) + 1);
	env[idx] = new_str;
}

void	append_env_variable(t_shell *shell, char *content)
{
	int		env_count;
	int		j;
	char	**new_env;

	env_count = 0;
	while (shell->env && shell->env[env_count])
		env_count++;
	new_env = ft_alloc(sizeof(char *) * (env_count + 2));
	j = 0;
	while (shell->env && shell->env[j])
	{
		new_env[j] = shell->env[j];
		j++;
	}
	new_env[j] = ft_strdup(content);
	new_env[j + 1] = NULL;
	shell->env = new_env;
}

void	ft_env(char **env_copy)
{
	int	i;

	i = 0;
	while (env_copy[i])
		printf("%s\n", env_copy[i++]);
}
