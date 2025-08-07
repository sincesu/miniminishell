#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <signal.h>

static int	ft_process_single_heredoc(t_shell *shell, t_redirect *redir)
{
	char	*heredoc_content;
	int		flag;

	flag = 0;
	if (redir->flags == S_WORD || redir->flags == D_WORD)
		flag = 1;
	if (redir->type == R_HERE && !redir->document)
	{
		heredoc_content = ft_get_heredoc_input(redir->file_name, shell, flag);
		if (heredoc_content == NULL && g_signal_received == SIGINT)
		{
			shell->exit_code = 130;
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