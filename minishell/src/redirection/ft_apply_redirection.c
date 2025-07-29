/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 03:16:28 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:22:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static int	ft_apply_input_redirection(t_redirect *redir)
{
	int	fd;

	fd = open(redir->file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	ft_apply_output_redirection(t_redirect *redir, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(redir->file_name, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	ft_apply_heredoc_redirection(t_redirect *redir)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	if (redir->document)
		ft_putstr_fd(redir->document, pipefd[1]);
	else
		write(pipefd[1], "", 0);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (0);
}

int	ft_apply_redirections(t_redirect *redir, int redirect_count, int i)
{
	while (i < redirect_count)
	{
		if (redir[i].type == R_IN)
		{
			if (ft_apply_input_redirection(&redir[i]) == -1)
				return (-1);
		}
		else if (redir[i].type == R_OUT)
		{
			if (ft_apply_output_redirection(&redir[i], 0) == -1)
				return (-1);
		}
		else if (redir[i].type == R_APPEND)
		{
			if (ft_apply_output_redirection(&redir[i], 1) == -1)
				return (-1);
		}
		else if (redir[i].type == R_HERE)
		{
			if (ft_apply_heredoc_redirection(&redir[i]) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
