/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:34:29 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/13 15:07:09 by saincesu         ###   ########.fr       */
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
			token->next->content[0] = '\0';
			remove_empty_tokens(&token);
		}
		token = token->next;
	}
}
