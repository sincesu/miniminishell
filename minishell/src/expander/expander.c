/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 08:49:50 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/15 13:52:02 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"
#include "../../include/minishell.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

char	*find_dollar(char *input, char **env, int flag)
{
	int		i;
	char	*expanded;
	int		var_start;
	char	*str;
	int		var_len;
	char	*tmp;
	
	i = 0;
	str = NULL;
	expanded = ft_strdup("");
	//sadece dolar olma kısmına da bak.
	if (flag == R_APPEND)
		return (input);
	while (input[i])
	{
		if (input[i] == '$')
		{
			var_start = i + 1;
			var_len = 0;
			while (ft_isalnum(input[var_start + var_len]) || input[var_start + var_len] == '_')
				var_len++;

			if (var_len > 0)
			{
				str = fill_dolar(&input[var_start], env, var_len);
				expanded = ft_strjoin(expanded, str);
				i = var_start + var_len;
			}
			else
			{
				tmp = ft_strdup("$");
				expanded = ft_strjoin(expanded, tmp);
				i++;
				continue;
			}
		}
		else
		{
			tmp = ft_alloc(2);
			tmp[0] = input[i];
			tmp[1] = '\0';
			expanded = ft_strjoin(expanded, tmp);
			i++;
		}
	}
	return (expanded);
}

char	*expand(char *input, t_shell *shell, int flag)
{
	char	*exit_code;
	char	*result;

	exit_code = NULL;
	result = NULL;
	if (input[0] == '~' && ft_strlen(input) == 1)
		ft_strlcpy(input, "$HOME", 6);
	if (input[0] == '$' && input[1] == '?')
	{
		exit_code = ft_itoa(shell->exit_code);
		result = ft_strjoin(exit_code, input + 2);
		return (result);
	}
	else
		input = find_dollar(input, shell->env, flag);
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
		if (!curr->content || curr->content[0] == '\0')
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
