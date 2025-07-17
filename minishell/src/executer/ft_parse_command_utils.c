#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <unistd.h>

void	ft_initialize_parser(t_parser *parser, t_parser parsed)
{
	parser->args = NULL;
	parser->redirect = NULL;
	parser->redirect_count = 0;
	parser->fd_in = STDIN_FILENO;
	parser->fd_out = STDOUT_FILENO;
	parser->prev = NULL;
	parser->next = NULL;
	*parser = parsed;
}

void	ft_count_args_redirects(t_token *tokens, int *arg_count, 
		int *redirect_count)
{
	t_token	*temp;
	int		prev_type;

	temp = tokens;
	*arg_count = 0;
	*redirect_count = 0;
	while (temp)
	{
		if (temp->type == S_WORD || temp->type == D_WORD || temp->type == U_WORD)
		{
            if (temp->prev)
                prev_type = temp->prev->type;
            else
                prev_type = 0;
			if (temp == tokens || !is_operator_type(prev_type))
				(*arg_count)++;
		}
		else if (is_operator_type(temp->type))
			(*redirect_count)++;
		temp = temp->next;
	}
}

static t_redirect	*ft_create_redirect(t_token *temp, t_shell *shell, 
		t_parser parser)
{
	t_redirect	*redir;

	redir = ft_alloc(sizeof(t_redirect));
	redir->type = temp->type;
	redir->flags = 0;
	redir->document = NULL;
	redir->next = NULL;
	if (temp->next && (temp->next->type == S_WORD || temp->next->type == D_WORD || temp->next->type == U_WORD))
	{
		redir->file_name = ft_strdup(temp->next->content);
		if (temp->type == R_HERE)
			redir->document = ft_get_heredoc_input(temp->next->content, 
					shell, parser);
	}
	return (redir);
}

t_redirect	*ft_process_redirects(t_shell *shell, t_parser parser)
{
	t_token		*temp;
	t_redirect	*head;
	t_redirect	*tail;
	t_redirect	*redir;

	head = NULL;
	tail = NULL;
	temp = shell->args;
	while (temp)
	{
		if (is_operator_type(temp->type))
		{
			redir = ft_create_redirect(temp, shell, parser);
			if (!head)
				head = redir;
			else
				tail->next = redir;
			tail = redir;
			if (temp->next && (temp->next->type == S_WORD || temp->next->type == D_WORD || temp->next->type == U_WORD))
				temp = temp->next;
		}
		temp = temp->next;
	}
	return (head);
}

void	ft_process_args(t_shell *shell, t_parser *parser)
{
	t_token	*temp;
	int		i;
	int		prev_type;

	temp = shell->args;
	i = 0;
	while (temp)
	{
		if (temp->type == S_WORD || temp->type == D_WORD || temp->type == U_WORD)
		{
            if (temp->prev)
                prev_type = temp->prev->type;
            else
                prev_type = 0;
			if (temp == shell->args || !is_operator_type(prev_type))
				parser->args[i++] = temp->content;
		}
		temp = temp->next;
	}
	parser->args[i] = NULL;
}
