/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:34:29 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 03:14:01 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"

void	merger(t_token *a)
{
	t_token	*curr;
	t_token	*next;

	curr = a;
	while (curr && curr->next)
	{
		if (curr->flag == 1)
		{
			next = curr->next;
			curr->content = ft_strjoin(curr->content, next->content);
			curr->flag = next->flag;
			curr->type = next->type;
			curr->next = next->next;
		}
		else
			curr = curr->next;
	}
}
