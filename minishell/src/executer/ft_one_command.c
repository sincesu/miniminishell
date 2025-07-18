#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

static void	ft_restore_std_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

static int	ft_handle_redirections(t_redirect *redir,
	int *saved_stdin, int *saved_stdout)
{
	if (!redir)
		return (0);
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (ft_apply_redirections(redir) == -1)
	{
		ft_restore_std_fds(*saved_stdin, *saved_stdout);
		return (-1);
	}
	return (0);
}

static int	ft_prepare_heredocs(t_shell *shell, t_parser *parsed)
{
	t_redirect	*redir;

	redir = parsed->redirect;
	while (redir)
	{
		if (redir->type == R_HERE && !redir->document)
			redir->document = ft_get_heredoc_input(redir->file_name,
					shell, *parsed);
		redir = redir->next;
	}
	return (0);
}

int	ft_one_command(t_shell *shell, t_parser *parsed)
{
	int			exit_code;
	int			saved_stdin;
	int			saved_stdout;

	if (!parsed->args || !parsed->args[0])
		return (1);
	ft_prepare_heredocs(shell, parsed);
	saved_stdin = -1;
	saved_stdout = -1;
	if (ft_handle_redirections(parsed->redirect,
			&saved_stdin, &saved_stdout) == -1)
		return (1);
	if (ft_is_builtin(parsed->args[0]))
		exit_code = ft_execute_builtin(shell, parsed);
	else
		exit_code = ft_shell_command(shell, parsed);
	ft_restore_std_fds(saved_stdin, saved_stdout);
	return (exit_code);
}
