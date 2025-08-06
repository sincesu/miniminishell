/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 10:28:39 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/05 13:56:05 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

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
			break ;
		}
		i++;
	}
	return (env);
}

void	underscore_value_changer(t_shell *shell, t_token *prev)
{
	int	i;

	i = 0;
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

void	set_underscore_env(t_token *a, t_shell *shell)
{
	t_token	*token;
	t_token	*prev;

	token = a;
	prev = NULL;
	while (token)
	{
		if (token->type == PIPE || (is_redirection_type(token->type)
				&& (!token->next->next || !token->next->next->content)))
			return ;
		prev = token;
		token = token->next;
	}
	if (!prev || !prev->content)
		return ;
	underscore_value_changer(shell, prev);
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
	return (copy_env);
}
