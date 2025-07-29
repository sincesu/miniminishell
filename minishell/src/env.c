/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:20:10 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:20:10 by saincesu         ###   ########.fr       */
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
	new_env = ft_alloc(sizeof(char *) * 4);
	new_env[0] = ft_strjoin("PWD=", cwd);
	new_env[1] = ft_strdup("SHLVL=1");
	new_env[2] = ft_strdup("_=./minishell");
	new_env[3] = NULL;
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

void	set_underscore_env(t_token *a, t_shell *shell)
{
	t_token	*token;
	t_token	*prev;
	int		i;

	i = 0;
	token = a;
	prev = NULL;
	while (token)
	{
		if (token->type == PIPE || (is_operator_type(token->type)
				&& (!token->next->next || !token->next->next->content)))
			return ;
		prev = token;
		token = token->next;
	}
	if (!prev || !prev->content)
		return ;
	while (shell->env[i])
	{
		if (shell->env[i][0] == '_' && shell->env[i][1] == '=')
		{
			if (!ft_strncmp(prev->content, "env", 3))
				shell->env[i] = ft_strdup("_=usr/bin/env");
			else
				shell->env[i] = ft_strjoin("_=", prev->content);
		}
		i++;
	}
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
		copy_env[i] = ft_strdup(env[i]);
		i++;
	}
	copy_env[env_line] = NULL;
	return (copy_env);
}
