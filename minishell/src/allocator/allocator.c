/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:51:48 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/25 12:51:48 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdlib.h>

t_mem_list	**get_head_mem(void)
{
	static t_mem_list	*head_list = NULL;

	return (&head_list);
}

void	ft_free(void)
{
	t_mem_list	**head_mem;
	t_mem_list	*cur_mem;
	t_mem_list	*next_mem;

	head_mem = get_head_mem();
	cur_mem = *head_mem;
	while (cur_mem != NULL)
	{
		next_mem = cur_mem->next;
		free(cur_mem->block);
		free(cur_mem);
		cur_mem = next_mem;
	}
}

void	safe_abort(int exit_code)
{
	ft_free();
	exit(exit_code);
}

void	register_alloc_mem(void *ptr)
{
	t_mem_list	*mem;
	t_mem_list	**head_mem;

	mem = malloc(sizeof(t_mem_list));
	if (mem == NULL)
	{
		free(ptr);
		safe_abort(1);
	}
	mem->block = ptr;
	mem->next = NULL;
	head_mem = get_head_mem();
	if (*head_mem == NULL)
		*head_mem = mem;
	else
	{
		mem->next = *head_mem;
		*head_mem = mem;
	}
}

void	*ft_alloc(unsigned long size)
{
	void	*ptr;

	ptr = ft_calloc(size, 1);
	if (ptr == NULL)
		safe_abort(1);
	register_alloc_mem(ptr);
	return (ptr);
}
