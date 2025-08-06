/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:31:49 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/05 13:59:07 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_parser	*ft_init_parser(t_parser *prev, t_token *token)
{
	t_parser	current;
	int			red_len_count;
	int			arg_len_count;

	red_len_count = red_len_counter(token);
	arg_len_count = arg_len_counter(token);
	current = (t_parser){
		.args = ft_alloc(sizeof(char *) * (arg_len_count + 1)),
		.redirect = ft_alloc(sizeof(t_redirect) * (red_len_count + 1)),
		.redirect_count = red_len_count,
		.fd_in = 0,
		.fd_out = 1,
		.prev = prev,
		.next = NULL,
	};
	current.args[arg_len_count] = NULL;
	return (new_node(current));
}

void	ft_addback_node(t_parser **head_node, t_parser *current)
{
	t_parser	*last;

	if (*head_node == NULL)
	{
		*head_node = current;
		current->prev = NULL;
	}
	else
	{
		last = *head_node;
		while (last->next != NULL)
			last = last->next;
		last->next = current;
		current->prev = last;
	}
}

void	set_redirect(t_token **token, t_redirect *redirect)
{
	redirect->type = (*token)->type;
	if (redirect->type == R_HERE)
		redirect->flags = 1;
	else
		redirect->flags = 0;
	if ((*token)->next)
	{
		*token = (*token)->next;
		redirect->file_name = (*token)->content;
		redirect->flags = (*token)->type;
		redirect->document = NULL;
	}
}

t_token	*ft_set_parser(t_token *token, t_parser *current)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token && token->type != PIPE)
	{
		if (is_redirection_type(token->type))
		{
			set_redirect(&token, &current->redirect[i]);
			i++;
		}
		else if (!is_redirection_type(token->type))
		{
			current->args[j++] = token->content;
		}
		token = token->next;
	}
	if (token && token->type == PIPE)
		return (token->next);
	return (token);
}

t_parser	*parser(t_token *token)
{
	t_parser	*head_node;
	t_parser	*current;

	head_node = NULL;
	while (token)
	{
		current = ft_init_parser(head_node, token);
		ft_addback_node(&head_node, current);
		token = ft_set_parser(token, current);
	}
	return (head_node);
}
