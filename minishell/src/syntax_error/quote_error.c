/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:41:07 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:22:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdio.h>

int	quote_error(char *input, t_shell *shell)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] != quote)
			{
				ft_putstr_fd("minishell: syntax error: unmatched quote\n", 2);
				shell->exit_code = 2;
				return (1);
			}
		}
		if (input[i])
			i++;
	}
	return (0);
}

int	operator_error(int c, t_shell *shell)
{
	if (c == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		shell->exit_code = 2;
		return (1);
	}
	return (0);
}
