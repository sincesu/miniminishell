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

int	ft_export_error(char *err)
{
	ft_putstr_fd("minishell: export: -", 2);
	ft_putchar_fd(err[1], 2);
	ft_putendl_fd(": invalid option", 2);
	return (2);
}

int	ft_export(t_shell *shell)
{
	t_token	*token;

	token = shell->args;
	if (shell->args->next && shell->args->next->type == U_WORD)
	{
		if (shell->args->next->content[0] == '-')
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
