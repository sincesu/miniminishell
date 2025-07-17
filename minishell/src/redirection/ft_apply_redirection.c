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
		return (perror("infile"), -1);
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
		if (append)
			perror("append");
		else
			perror("outfile");
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
		return (perror("heredoc pipe"), -1);
	if (redir->document)
		ft_putstr_fd(redir->document, pipefd[1]);
	else
		write(pipefd[1], "", 0);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (0);
}

int	ft_apply_redirections(t_redirect *redir)
{
	while (redir)
	{
		if (redir->type == R_IN)
		{
			if (ft_apply_input_redirection(redir) == -1)
				return (-1);
		}
		else if (redir->type == R_OUT)
		{
			if (ft_apply_output_redirection(redir, 0) == -1)
				return (-1);
		}
		else if (redir->type == R_APPEND)
		{
			if (ft_apply_output_redirection(redir, 1) == -1)
				return (-1);
		}
		else if (redir->type == R_HERE)
		{
			if (ft_apply_heredoc_redirection(redir) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}
