/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 08:49:50 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/01 10:22:44 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"
#include "../../include/minishell.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

char	*find_dollar(char *input, char **env, int flag, int exit_code)
{
	int		i;
	char	*expanded;
	char	*exit;

	i = 0;
	expanded = ft_strdup("");
	if (flag == R_HERE)
		return (input);
	while (input[i])
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
			{
				exit = ft_itoa(exit_code);
				expanded = ft_strjoin(expanded, exit);
				i += 2;
			}
			else if (ft_isalnum(input[i + 1]) || input[i + 1] == '_')
				i += handle_var_expand(input + i, env, &expanded);
			else
				i += handle_normal_char(input + i, &expanded);
		}
		else
			i += handle_normal_char(input + i, &expanded);
	}
	return (expanded);
}

// char	*expand(char *input, t_shell *shell, int flag)
// {
// 	char	*exit_code;
// 	char	*result;

// 	exit_code = NULL;
// 	result = NULL;
// 	if (input[0] == '~' && ft_strlen(input) == 1)
// 		input = ft_strdup("$HOME");
// 	if (input[0] == '$' && input[1] == '?')
// 	{
// 		exit_code = ft_itoa(shell->exit_code);
// 		result = ft_strjoin(exit_code, input + 2);
// 		result = find_dollar(result, shell->env, flag);
// 		return (result);
// 	}
// 	else
// 		input = find_dollar(input, shell->env, flag);
// 	return (input);
// }

char	*expand(char *input, t_shell *shell, int flag)
{
	if (input[0] == '~' && ft_strlen(input) == 1)
		input = ft_strdup("$HOME");
	input = find_dollar(input, shell->env, flag, shell->exit_code);
	return (input);
}

char	*remove_outer_quote_all(char *s)
{
	int		i;
	int		j;
	int		len;
	char	quote;
	char	*result;

	len = ft_strlen(s);
	result = ft_alloc(len + 1);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				result[j++] = s[i++];
			if (s[i] == quote)
				i++;
		}
		else
			result[j++] = s[i++];
	}
	result[j] = '\0';
	return (result);
}

void	remove_empty_tokens(t_token **head)
{
	t_token	*curr;
	t_token	*prev;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if ((!curr->content || curr->content[0] == '\0')
			&& !(curr->type == D_WORD || curr->type == S_WORD))
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			if (prev)
				curr = prev->next;
			else
				curr = *head;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void	expander(t_shell *shell)
{
	t_token	*args;
	int		x;

	x = 0;
	args = shell->args;
	while (args)
	{
		if (args->type == D_WORD || args->type == S_WORD)
			args->content = remove_outer_quote_all(args->content);
		if (args->type != S_WORD)
			args->content = expand(args->content, shell, x);
		x = args->type;
		args = args->next;
	}
	remove_empty_tokens(&(shell->args));
}
