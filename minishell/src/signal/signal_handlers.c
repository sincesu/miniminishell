/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 03:16:17 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:22:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <readline/readline.h>

void	ft_prompt_handler(int signum)
{
	g_signal_received = signum;
	ft_putendl_fd("", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigquit_handler(int signum)
{
	g_signal_received = signum;
	ft_putendl_fd("Quit (core dumped)", 2);
}

void	ft_execute_handler(int signum)
{
	g_signal_received = signum;
	ft_putendl_fd("", 1);
}

void	ft_heredoc_handler(int signum)
{
	g_signal_received = signum;
	rl_done = 1;
}
