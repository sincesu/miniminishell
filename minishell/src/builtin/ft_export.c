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
		if (handle_export_arg(shell, token->content))
			return (1);
		token = token->next;
	}
	return (0);
}
