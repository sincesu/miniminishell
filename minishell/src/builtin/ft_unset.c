/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:16:57 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/07 22:54:55 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdlib.h>

static int	is_remove_env(char *env_var, char **str)
{
	int		name_len;
	int		x;

	x = 0;
	name_len = 0;
	while (str[x])
	{
		name_len = ft_strlen(str[x]);
		if (ft_strncmp(env_var, str[x], name_len) == 0
			&& env_var[name_len] == '=')
			return (1);
		x++;
	}
	return (0);
}

static char	**copy_env_without_unset(char **env, char **str)
{
	int		i;
	int		j;
	int		env_count;
	char	**new_env;

	i = 0;
	j = 0;
	env_count = 0;
	while (env && env[env_count])
		env_count++;
	new_env = ft_alloc(sizeof(char *) * (env_count + 1));
	i = 0;
	while (env && env[i])
	{
		if (!is_remove_env(env[i], str))
		{
			new_env[j] = env[i];
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	ft_unset(t_shell *shell, t_parser *parsed)
{
	char		**new_env;

	if (parsed->args[1])
	{
		if (parsed->args[1][0] == '-')
		{
			ft_putstr_fd("minishell: unset: -", 2);
			ft_putchar_fd(parsed->args[1][1], 2);
			ft_putendl_fd(": invalid option", 2);
			return (2);
		}
	}
	if (!parsed->args[0] || !parsed->args[1])
		return (0);
	new_env = copy_env_without_unset(shell->env, parsed->args);
	shell->env = new_env;
	return (0);
}
