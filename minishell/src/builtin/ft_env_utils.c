/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 10:28:39 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/10 21:06:47 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	**empty_env(void)
{
	char	**new_env;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	new_env = ft_alloc(sizeof(char *) * 4);
	new_env[0] = ft_strjoin("PWD=", cwd);
	new_env[1] = ft_strdup("SHLVL=1");
	new_env[2] = ft_strdup("_=./minishell");
	new_env[3] = NULL;
	free(cwd);
	return (new_env);
}

static char	**update_shell_lvl(char **env)
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
			break ;
		}
		i++;
	}
	return (env);
}

char	**copy_env(char **env)
{
	int		i;
	int		env_len;
	char	**copy_env;

	env_len = 0;
	i = 0;
	copy_env = NULL;
	while (env && env[env_len])
		env_len++;
	copy_env = ft_alloc(sizeof(char *) * (env_len + 1));
	while (i < env_len)
	{
		copy_env[i] = ft_strdup(env[i]);
		i++;
	}
	copy_env[env_len] = NULL;
	copy_env = update_shell_lvl(copy_env);
	return (copy_env);
}

void	remove_export_only_variable(t_shell *shell, const char *name)
{
	int		i;
	int		cnt;
	int		keep;
	char	**new_list;

	cnt = 0;
	while (shell->export_only_list && shell->export_only_list[cnt])
		cnt++;
	new_list = ft_alloc(sizeof(char *) * (cnt + 1));
	keep = 0;
	i = 0;
	while (shell->export_only_list && shell->export_only_list[i])
	{
		if (ft_strncmp(shell->export_only_list[i], name,
				ft_strlen(name) + 1) != 0)
			new_list[keep++] = shell->export_only_list[i];
		i++;
	}
	new_list[keep] = NULL;
	shell->export_only_list = new_list;
}
