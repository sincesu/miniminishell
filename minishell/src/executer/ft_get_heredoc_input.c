/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_heredoc_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 03:16:40 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/01 19:14:20 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <signal.h>

char	*ft_line_func(t_shell *shell, char *result, char *line)
{
	char	*expanded;

	expanded = find_dollar(line, shell->env, 0, shell->exit_code);
	result = ft_strjoin(result, expanded);
	return (result);
}

static void	ft_print_eof_warning(const char *delimiter)
{
	ft_putstr_fd("minishell: warning: ", 2);
	ft_putstr_fd("here-document delimited by end-of-file ", 2);
	ft_putstr_fd("(wanted `", 2);
	ft_putstr_fd((char *)delimiter, 2);
	ft_putendl_fd("')", 2);
}

static char	*ft_process_line(t_shell *shell, char *result, char *line, int flag)
{
	char	*temp;

	if (flag)
		temp = ft_strjoin(result, line);
	else
		temp = ft_line_func(shell, result, line);
	result = ft_strjoin(temp, "\n");
	return (result);
}

static char	*ft_handle_signal_interrupt(char *line)
{
	free(line);
	return (NULL);
}

char	*ft_get_heredoc_input(const char *delimiter, t_shell *shell, int flag)
{
	char	*line;
	char	*result;

	result = ft_strdup("");
	ft_init_signals(HEREDOC);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_print_eof_warning(delimiter);
			break ;
		}
		if (g_signal_received == SIGINT)
			return (ft_handle_signal_interrupt(line));
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		result = ft_process_line(shell, result, line, flag);
		free(line);
	}
	ft_init_signals(PROMPT);
	return (result);
}
