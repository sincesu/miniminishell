/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:34:29 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/17 17:19:34 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"

void	merger(t_token	*a)
{
	t_token	*token;

	token = a;
	while (token)
	{
		while (token->flag == 1 && token->next)
		{
			token->content = ft_strjoin((char const *)token->content,
					(char const *)token->next->content);
			token->next->content = NULL;
			remove_empty_tokens(&token);
		}
		token = token->next;
	}
}
