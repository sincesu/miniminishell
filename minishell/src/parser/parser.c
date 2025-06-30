/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:31:49 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/30 18:17:20 by saincesu         ###   ########.fr       */
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
		if (ft_strncmp(a->content, ">", 1) == 0 && a->next && a->next->content)
			parsed->output = ft_strdup(a->next->content);
		else if (ft_strncmp(a->content, ">>", 2) == 0 && a->next && a->next->content)
			parsed->output = ft_strdup(a->next->content);
		else if (ft_strncmp(a->content, "<", 1) == 0 && a->next && a->next->content)
			parsed->input = ft_strdup(a->next->content);
		else if (a->content[0] == '-')
			parsed->flags[i++] = ft_strdup(a->content);
		else if (!is_operator(a->content[0])) // bu satıra bak > b yazınca b'yi de argsa atıyor
			parsed->args[j++] = ft_strdup(a->content);
		// else if heredoc yazcam.
		a = a->next;
	}
	parsed->flags[i] = NULL;
	parsed->args[j] = NULL;
}
