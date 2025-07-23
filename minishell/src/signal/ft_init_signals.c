/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:19:42 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:19:42 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <readline/readline.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int	g_signal_received = 0;

static int	ft_dummy_event_hook(void)
{
	return (0);
}

void	ft_init_signals(t_signal_type context_type)
{
	g_signal_received = 0;
	if (context_type == PROMPT)
	{
		rl_event_hook = NULL;
		signal(SIGINT, ft_prompt_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (context_type == EXECUTION)
	{
		rl_event_hook = NULL;
		signal(SIGINT, ft_execute_handler);
		signal(SIGQUIT, ft_sigquit_handler);
	}
	else if (context_type == HEREDOC)
	{
		rl_event_hook = ft_dummy_event_hook;
		signal(SIGINT, ft_heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
