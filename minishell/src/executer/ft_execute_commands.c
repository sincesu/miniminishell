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
#include <unistd.h>

void	ft_safe_close_fds(t_parser *parsed)
{
	if (parsed->fd_in != STDIN_FILENO)
		close(parsed->fd_in);
	if (parsed->fd_out != STDOUT_FILENO)
		close(parsed->fd_out);
}

void	ft_execute_commands(t_shell *shell, t_parser *parsed)
{
	if (parsed->next != NULL)
		shell->exit_code = ft_multi_command(shell, parsed);
	else
		shell->exit_code = ft_one_command(shell, parsed);
}
