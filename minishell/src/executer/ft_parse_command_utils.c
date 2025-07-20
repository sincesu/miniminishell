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

	*arg_count = 0;
	*redirect_count = 0;
	temp = tokens;
	while (temp)
	{
		if (temp->type == S_WORD || temp->type == D_WORD
			|| temp->type == U_WORD)
		{
			if (!temp->prev || !is_operator_type(temp->prev->type))
				(*arg_count)++;
		}
		else if (is_operator_type(temp->type))
			(*redirect_count)++;
		temp = temp->next;
	}
}

void	ft_process_args(t_shell *shell, t_parser *parser)
{
	t_token	*temp;
	int		i;

	temp = shell->args;
	i = 0;
	while (temp)
	{
		if (is_operator_type(temp->type))
		{
			if (temp->next)
				temp = temp->next;
		}
		else if ((temp->type == S_WORD || temp->type == D_WORD
				|| temp->type == U_WORD))
		{
			if (!temp->prev || !is_operator_type(temp->prev->type))
			{
				parser->args[i++] = temp->content;
			}
		}
		temp = temp->next;
	}
	parser->args[i] = NULL;
}
