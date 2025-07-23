/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 03:16:52 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 03:16:53 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static t_redirect	*ft_create_redirect(t_token *temp, t_shell *shell)
{
	t_redirect	*redir;

	redir = ft_alloc(sizeof(t_redirect));
	redir->type = temp->type;
	redir->flags = 0;
	redir->document = NULL;
	redir->next = NULL;
	if (temp->next && (temp->next->type == S_WORD
			|| temp->next->type == D_WORD || temp->next->type == U_WORD))
	{
		redir->file_name = ft_strdup(temp->next->content);
		if (temp->type == R_HERE)
			redir->document = ft_get_heredoc_input(temp->next->content,
					shell);
	}
	return (redir);
}

static void	skip_redirect_target(t_token **temp)
{
	if ((*temp)->next && ((*temp)->next->type == S_WORD
			|| (*temp)->next->type == D_WORD
			|| (*temp)->next->type == U_WORD))
		*temp = (*temp)->next;
}

static t_redirect	*ft_process_redirects(t_shell *shell)
{
	t_token		*temp;
	t_redirect	*head;
	t_redirect	*tail;
	t_redirect	*redir;

	temp = shell->args;
	head = NULL;
	tail = NULL;
	while (temp)
	{
		if (is_operator_type(temp->type))
		{
			redir = ft_create_redirect(temp, shell);
			if (!head)
				head = redir;
			else
				tail->next = redir;
			tail = redir;
			skip_redirect_target(&temp);
		}
		temp = temp->next;
	}
	return (head);
}

t_parser	ft_parse_command(t_shell *shell, t_parser parsed)
{
	t_parser	parser;
	int			arg_count;
	int			redirect_count;

	ft_initialize_parser(&parser, parsed);
	ft_count_args_redirects(shell->args, &arg_count, &redirect_count);
	parser.args = ft_alloc(sizeof(char *) * (arg_count + 1));
	parser.redirect_count = redirect_count;
	parser.redirect = ft_process_redirects(shell);
	ft_process_args(shell, &parser);
	return (parser);
}
