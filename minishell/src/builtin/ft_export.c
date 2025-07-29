/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:13:03 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/29 20:34:00 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdio.h>

static int	check_export_arg(t_shell *shell, char *arg)
{
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("\': not a valid identifier", 2);
		shell->exit_code = 1;
		return (1);
	}
	return (0);
}

static int	merge_env_and_export_list(char **dst, char **env, char **export)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env && env[j])
	{
		if (env[j][0] != '_')
			dst[i++] = env[j];
		j++;
	}
	j = 0;
	while (export && export[j])
		dst[i++] = export[j++];
	dst[i] = NULL;
	return (0);
}

static void	print_sorted_list(char **combined)
{
	int		i;
	char	*eq;

	i = 0;
	while (combined[i])
	{
		eq = ft_strchr(combined[i], '=');
		if (eq)
			printf("declare -x %.*s=\"%s\"\n", (int)(eq - combined[i]),
				combined[i], eq + 1);
		else
			printf("declare -x %s\n", combined[i]);
		i++;
	}
}

static void	export_list_printer(t_shell *shell)
{
	int		env_len;
	int		exp_len;
	int		i;
	char	**combined;

	env_len = 0;
	exp_len = 0;
	i = 0;
	while (shell->env && shell->env[env_len])
		env_len++;
	while (shell->export_only_list && shell->export_only_list[exp_len])
		exp_len++;
	combined = ft_alloc(sizeof(char *) * (env_len + exp_len + 1));
	merge_env_and_export_list(combined, shell->env, shell->export_only_list);
	bubble_sort(combined);
	print_sorted_list(combined);
}

int	ft_export(t_shell *shell)
{
	t_token	*token;

	token = shell->args;
	if (!token->next || (token->next
			&& is_operator_token(token->next->content)))
	{
		export_list_printer(shell);
		return (0);
	}
	token = token->next;
	while (token)
	{
		if (is_operator_token(token->content))
			break ;
		if (check_export_arg(shell, token->content))
			return (1);
		if (handle_export_arg(shell, token->content))
			return (1);
		token = token->next;
	}
	return (0);
}
