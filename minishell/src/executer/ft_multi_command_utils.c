/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_command_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:53:23 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/06 21:12:34 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

void	init_command_redirections(t_parser *parsed, int **pipes,
		int cmd_count)
{
	if (parsed->fd_in != STDIN_FILENO
		&& dup2(parsed->fd_in, STDIN_FILENO) == -1)
	{
		ft_close_all_pipes(pipes, cmd_count - 1);
		close(parsed->fd_in);
		safe_abort(1);
	}
	if (parsed->fd_out != STDOUT_FILENO
		&& dup2(parsed->fd_out, STDOUT_FILENO) == -1)
	{
		ft_close_all_pipes(pipes, cmd_count - 1);
		close(parsed->fd_out);
		safe_abort(1);
	}
	if (parsed->redirect && ft_apply_redirections(parsed->redirect,
			parsed->redirect_count, 0) == -1)
	{
		ft_close_all_pipes(pipes, cmd_count - 1);
		if (parsed->fd_in != STDIN_FILENO)
			close(parsed->fd_in);
		if (parsed->fd_out != STDOUT_FILENO)
			close(parsed->fd_out);
		safe_abort(1);
	}
}

int	ft_count_commands(t_parser *parsed)
{
	int	count;

	count = 0;
	while (parsed)
	{
		count++;
		parsed = parsed->next;
	}
	return (count);
}

int	ft_create_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pipes[i] = ft_alloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_close_all_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
