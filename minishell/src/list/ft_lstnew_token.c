/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:52:25 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/23 14:41:51 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

t_token	*ft_lstnew_token(t_token token)
{
	t_token	*new_node;

	new_node = ft_alloc(sizeof(t_token));
	*new_node = token; //shallow copy(yüzeysel kopyalama)
	new_node->next = NULL;
	return (new_node);
}

//allocator düzelt- lexer düzelt- expander yaz.