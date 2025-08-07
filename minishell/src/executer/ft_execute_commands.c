/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:53:01 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/07 18:57:09 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_is_multi_command(t_shell shell)
{
	t_token	*token;

	token = shell.args;
	while (token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

void	ft_execute_commands(t_shell *shell, t_parser *parsed)
{
	if (ft_is_multi_command(*shell))
		shell->exit_code = ft_multi_command(shell, parsed);
	else
		shell->exit_code = ft_one_command(shell, parsed);
}
