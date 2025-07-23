/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_heredoc_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 03:16:40 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:22:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <readline/readline.h>
#include <stdlib.h>

char	*ft_get_heredoc_input(const char *delimiter, t_shell *shell)
{
	char	*line;
	char	*result;
	char	*temp;

	result = ft_strdup("");
	ft_init_signals(HEREDOC);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			safe_abort(0);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		temp = ft_strjoin(result, find_dollar(line, shell->env, 0));
		free(line);
		result = ft_strjoin(temp, "\n");
	}
	ft_init_signals(PROMPT);
	return (result);
}
