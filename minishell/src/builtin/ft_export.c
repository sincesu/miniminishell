/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:13:03 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/07 22:55:42 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdio.h>

static int	check_export_arg(t_shell *shell, char *arg)
{
	int	i;
	int	str_len;
	int	x;

	str_len = ft_strlen(arg);
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			str_len = i;
			break ;
		}
		i++;
	}
	x = is_valid_identifier(shell, arg, str_len);
	if (x != 0)
		return (x);
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
	char	**combined;

	env_len = 0;
	exp_len = 0;
	while (shell->env && shell->env[env_len])
		env_len++;
	while (shell->export_only_list && shell->export_only_list[exp_len])
		exp_len++;
	combined = ft_alloc(sizeof(char *) * (env_len + exp_len + 1));
	merge_env_and_export_list(combined, shell->env, shell->export_only_list);
	bubble_sort(combined);
	print_sorted_list(combined);
}

int	ft_export(t_shell *shell, t_parser *parsed)
{
	char	**str;
	int		i;
	int		x;

	i = 1;
	str = parsed->args;
	if (!str[1] || (str[1] && is_operator_token(str[1])))
	{
		export_list_printer(shell);
		return (0);
	}
	while (str[i])
	{
		if (is_operator_token(str[i]))
			break ;
		x = check_export_arg(shell, str[i]);
		if (x != 0)
			return (x);
		handle_export_arg(shell, str[i]);
		i++;
	}
	return (0);
}
