/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:51:44 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:22:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stddef.h>

void	ft_lstadd_back_token(t_token **lst, t_token *new_node)
{
	t_token	*last;

	if (!lst || !new_node)
		return ;
	if (*lst)
	{
		last = ft_lstlast_token(*lst);
		last->next = new_node;
	}
	else
		*lst = new_node;
}
