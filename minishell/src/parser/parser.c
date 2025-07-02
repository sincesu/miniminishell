/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:31:49 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/02 05:00:49 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	parser(t_shell *shell, t_parser *parsed)
{
	t_token *a;
	int i;
	int j;
	int flag_count;
	int arg_count;

	i = 0;
	j = 0;
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
	parsed->input = NULL;
	parsed->output = NULL;
	a = shell->args;
	
	if (a && a->content)
	{
		parsed->command = a->content;
		a = a->next;
	}
	while (a && a->content)
	{
		if ((strcmp(a->content, ">") == 0 || strcmp(a->content, ">>") == 0) && a->next && a->next->content)
		{
			parsed->output = ft_strdup(a->next->content);
			a = a->next;
		}
		else if ((strcmp(a->content, "<") == 0 || strcmp(a->content, "<<") == 0) && a->next && a->next->content)
		{
			parsed->input = ft_strdup(a->next->content);
			a = a->next;
		}
		else if (a->content[0] == '-')
			parsed->flags[i++] = ft_strdup(a->content);
		else if (!is_operator(a->content[0]))
			parsed->args[j++] = ft_strdup(a->content); 
		a = a->next;
	}
	//redirection'un yanındakini sadece args'a 
	parsed->flags[i] = NULL;
	parsed->args[j] = NULL;
}
