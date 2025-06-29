/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:31:49 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/29 18:08:27 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

void	parser(t_shell *shell, t_parser *parsed)
{
	t_token *a;
	int i;
	int flag_count;
	int arg_count;

	i = 0;
	flag_count = 0;
	arg_count = 0;
	a = shell->args;
	while (a)
	{
		if (a->content && a->content[0] == '-')
			flag_count++;
		else if (a->content && !is_operator(a->content[0]))
			arg_count++;
		a = a->next;
	}
	parsed->flags = ft_alloc(sizeof(char *) * (flag_count + 1));
	parsed->args = ft_alloc(sizeof(char *) * (arg_count + 1));
	a = shell->args;
	if (a && a->content)
	{
		parsed->command = a->content;
		a = a->next;
	}
	while (a && a->content && a->content[0] == '-')
	{
		parsed->flags[i++] = ft_strdup(a->content);
		a = a->next;
	}
	parsed->flags[i] = NULL;
	i = 0;
	while (a && a->content && !is_operator(a->content[0]))
	{
		parsed->args[i++] = ft_strdup(a->content);
		a = a->next;
	}
	parsed->args[i] = NULL;
}








/*void	parser(t_shell *shell, t_parser *parsed)
{
	if (shell->args->content)
		shell->args->content = parsed->command;
	if (shell->args->next->content && shell->args->next->content[0] == '-')
		shell->args->content = parsed->flags;
	else if (shell->args->next->content)
		shell->args->next->content = parsed->
}*/