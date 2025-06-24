/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:51:44 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/23 16:14:43 by saincesu         ###   ########.fr       */
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
