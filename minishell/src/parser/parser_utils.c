/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:30:08 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:22:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	red_len_counter(t_token *token)
{
	int	red_len_count;

	red_len_count = 0;
	while (token && token->type != PIPE)
	{
		if (is_operator_type(token->type))
			red_len_count++;
		token = token->next;
	}
	return (red_len_count);
}

int	arg_len_counter(t_token *token)
{
	int	arg_len_count;

	arg_len_count = 0;
	while (token && token->type != PIPE)
	{
		if (!is_operator_type(token->type))
			arg_len_count++;
		token = token->next;
	}
	return (arg_len_count);
}

t_parser	*new_node(t_parser current)
{
	t_parser	*new_node;

	new_node = ft_alloc(sizeof(t_parser));
	*new_node = current;
	return (new_node);
}
