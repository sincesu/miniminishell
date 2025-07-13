/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:52:25 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/13 15:06:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

t_token	*ft_lstnew_token(t_token token)
{
	t_token	*new_node;

	new_node = ft_alloc(sizeof(t_token));
	*new_node = token;
	new_node->next = NULL;
	return (new_node);
}
