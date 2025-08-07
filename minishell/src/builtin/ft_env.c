/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:12:28 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/07 18:54:34 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"
#include "../../include/minishell.h"
#include <signal.h>

int	is_valid_identifier(t_shell *shell, char *arg, int str_len)
{
	int	i;

	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		shell->exit_code = 1;
		return (0);
	}
	i = 0;
	while (arg[i] && i < str_len)
	{
		if (arg[i] == '-')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(arg, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			shell->exit_code = 2;
			return (0);
		}
		i++;
	}
	return (1);
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

int	ft_env(t_shell *shell)
{
	int	i;

	if (shell->args->next)
	{
		if (shell->args->next->content[0] == '-')
		{
			ft_putstr_fd("minishell: env: invalid option -- \'", 2);
			ft_putchar_fd(shell->args->next->content[1], 2);
			ft_putendl_fd("\'", 2);
			return (125);
		}
		else
		{
			ft_putstr_fd("minishell: env: \'", 2);
			ft_putstr_fd(shell->args->next->content, 2);
			ft_putendl_fd("\': invalid argument", 2);
			return (127);
		}
	}
	signal(SIGPIPE, SIG_IGN);
	i = 0;
	while (shell->env[i])
		ft_putendl_fd(shell->env[i++], 1);
	return (0);
}
