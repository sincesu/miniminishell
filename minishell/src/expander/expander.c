/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 08:49:50 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/10 18:00:55 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"
#include "../../include/minishell.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

char	*find_dollar(char *input, char **env, int flag)
{
	int i;
	int var_len;
	char *str;
	char *env_val;
	char *expanded;

	str = NULL;
	env_val = NULL;
	i = 0;
	if (input[0] != '$'|| flag == R_HERE)
		return (input);

	input++;
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	var_len = i;
	if (var_len == 0)
		return (input - 1); //sadece $ varsa $'ı da geri ekle
	
	str = ft_substr(input, 0, var_len);

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, var_len) == 0 && env[i][var_len] == '=')
		{
			env_val = ft_strchr(env[i], '=') + 1;
			break;
		}
		i++;
	}
	if (env_val)
		expanded = ft_strjoin(env_val, input + var_len);
	else
		return (NULL);
	return (expanded);
}

char *expand(char *input, t_shell *shell, int flag)
{
	if (input[0] == '~' && ft_strlen(input) == 1)
		ft_strlcpy(input, "$HOME", 6);
	if (input[0] == '$' && input[1] == '?' && ft_strlen(input) == 2)
	{
		input = ft_itoa(shell->exit_code); //bunuda freelemek lazım ve inputu da freelemek lazım
	}
	else
		input = find_dollar(input, shell->env, flag);
	return (input);
}

char	*remove_outer_quote_all(char *s)
{
	int len = ft_strlen(s);
	char *result = ft_alloc(len + 1); // kendi alloc fonksiyonunu kullandım
	int i = 0, j = 0;

	while (s[i])
	{
		if (is_quote(s[i]))
		{
			char quote = s[i++];
			while (s[i] && s[i] != quote)
				result[j++] = s[i++];
			if (s[i] == quote)
				i++; // kapanış tırnağını geç
		}
		else
			result[j++] = s[i++];
	}
	result[j] = '\0';
	return result;
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
				*head = curr->next; //baştaki node'u atladım
		
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
	t_token *args;
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