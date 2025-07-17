/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:13:03 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/17 19:37:39 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdio.h>

void	export_list_printer(t_shell *shell)
{
	int		i;
	char	*eq;

	i = 0;
	while (shell->env && shell->env[i])
	{
		eq = ft_strchr(shell->env[i], '=');
		if (eq)
			printf("declare -x %.*s=\"%s\"\n", (int)(eq - shell->env[i]),
				shell->env[i], eq + 1);
		else
			printf("declare -x %s\n", shell->env[i]);
		i++;
	}
	i = 0;
	while (shell->export_only_list && shell->export_only_list[i])
		printf("declare -x %s\n", shell->export_only_list[i++]);
}

void	export_only_variable_append(t_shell *shell, char *content)
{
	int		i;
	char	**tmp;

	i = 0;
	while (shell->export_only_list && shell->export_only_list[i])
		i++;
	tmp = ft_alloc(sizeof(char *) * (i + 2));
	i = 0;
	while (shell->export_only_list && shell->export_only_list[i])
	{
		tmp[i] = shell->export_only_list[i];
		i++;
	}
	tmp[i] = ft_strdup(content);
	tmp[i + 1] = NULL;
	shell->export_only_list = tmp;
}

void	add_export_only_variable(t_shell *shell, char *content)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (shell->export_only_list && shell->export_only_list[i])
	{
		if (ft_strncmp(shell->export_only_list[i], content,
				ft_strlen(content) + 1) == 0)
			found = 1;
		i++;
	}
	if (!found)
		export_only_variable_append(shell, content);
}

int	check_export_arg(t_shell *shell, char *arg)
{
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg);
		shell->exit_code = 1;
		return (1);
	}
	return (0);
}

int	handle_export_arg(t_shell *shell, char *arg)
{
	char	*eq;
	char	*name;
	int		len;
	int		idx;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		len = eq - arg;
		name = ft_alloc(len + 1);
		ft_strlcpy(name, arg, len + 1);
		idx = find_in_env_index(shell->env, name);
		if (idx != -1)
			update_env_value(shell->env, idx, name, eq);
		else
			append_env_variable(shell, arg);
	}
	else
	{
		add_export_only_variable(shell, arg);
	}
	return (0);
}

int	ft_export(t_shell *shell)
{
	t_token	*token;

	token = shell->args;
	if (!token->next)
	{
		export_list_printer(shell);
		return (0);
	}
	token = token->next;
	while (token)
	{
		if (check_export_arg(shell, token->content))
			return (1);
		if(handle_export_arg(shell, token->content))
			return (1);
		token = token->next;
	}
	return (0);
}
