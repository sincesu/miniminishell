/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:42:22 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/13 14:42:22 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../Libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**empty_env(void)
{
	char	**new_env;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	new_env = ft_alloc(sizeof(char *) * 5);
	new_env[0] = ft_strjoin("PWD=", cwd);
	new_env[1] = ft_strdup("SHLVL=1");
	new_env[2] = ft_strdup("OLDPWD=");
	new_env[3] = ft_strdup("_=/usr/bin/env");
	new_env[4] = NULL;
	free(cwd);
	return (new_env);
}

char	**update_shell_lvl(char **env)
{
	int		i;
	int		shlvl;
	char	*new_shlvl;
	char	**new_env;

	i = 0;
	if (!env || !env[0])
	{
		new_env = empty_env();
		return (new_env);
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			shlvl = ft_atoi(env[i] + 6);
			shlvl++;
			new_shlvl = ft_strdup("SHLVL=");
			new_shlvl = ft_strjoin(new_shlvl, ft_itoa(shlvl));
			env[i] = new_shlvl;
		}
		i++;
	}
	return (env);
}

char	**copy_env(char **env)
{
	int		i;
	int		env_line;
	char	**copy_env;

	i = 0;
	copy_env = NULL;
	env_line = env_len(env);
	copy_env = ft_alloc(sizeof(char *) * (env_line + 1));
	while (i < env_line)
	{
		if (env[i][0] == '_' && env[i][1] == '=')
			copy_env[i] = ft_strdup("_=/usr/bin/env");
		else
			copy_env[i] = ft_strdup(env[i]);
		i++;
	}
	copy_env[env_line] = NULL;
	return (copy_env);
}
