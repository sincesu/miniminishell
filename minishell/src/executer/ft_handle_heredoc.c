/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merozcan <merozcan@student.42kocaeli.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:03:18 by merozcan          #+#    #+#             */
/*   Updated: 2025/08/08 01:03:19 by merozcan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stddef.h>
#include <signal.h>

static int	ft_process_single_heredoc(t_shell *shell, t_redirect *redir)
{
	char	*heredoc_content;
	int		flag;

	flag = 0;
	if (redir->flags == S_WORD || redir->flags == D_WORD)
		flag = 1;
	if (redir->type == R_HERE)
	{
		heredoc_content = ft_get_heredoc_input(redir->file_name, shell, flag);
		if (heredoc_content == NULL && g_signal_received == SIGINT)
		{
			shell->exit_code = 130;
			ft_init_signals(PROMPT);
			return (1);
		}
		redir->document = heredoc_content;
	}
	if (g_signal_received != 0)
		return (1);
	return (0);
}

static int	ft_prepare_heredocs(t_shell *shell, t_parser *parsed)
{
	t_redirect	*redir;
	int			i;

	redir = parsed->redirect;
	if (!redir)
		return (0);
	i = 0;
	while (i < parsed->redirect_count)
	{
		if (ft_process_single_heredoc(shell, &redir[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_handle_heredoc(t_shell *shell, t_parser *parsed)
{
	while (parsed != NULL)
	{
		if (ft_prepare_heredocs(shell, parsed))
			return (1);
		parsed = parsed->next;
	}
	return (0);
}
