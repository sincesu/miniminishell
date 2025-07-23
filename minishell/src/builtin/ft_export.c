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

static int	ft_export_error(char *err)
{
	ft_putstr_fd("minishell: export: -", 2);
	ft_putchar_fd(err[1], 2);
	ft_putendl_fd(": invalid option", 2);
	return (2);
}

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

static void	export_list_printer(t_shell *shell)
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

int	ft_export(t_shell *shell)
{
	t_token	*token;

	token = shell->args;
	if (token->next && token->next->type == U_WORD)
	{
		if (token->next->content[0] == '-')
			return (ft_export_error(shell->args->next->content));
	}
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
		if (handle_export_arg(shell, token->content))
			return (1);
		token = token->next;
	}
	return (0);
}
