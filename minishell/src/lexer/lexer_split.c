/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 01:18:00 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/10 16:36:47 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"
#include "../../include/minishell.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static int	is_operator_token(const char *s)
{
	if (s[0] == '>' && s[1] == '>')
		return (2);
	if (s[0] == '<' && s[1] == '<')
		return (2);
	if (s[0] == '>')
		return (1);
	if (s[0] == '<')
		return (1);
	if (s[0] == '|')
		return (1);
	return (0);
}

static int next_chunk_len(const char *s)
{
	int op_len;

	op_len = is_operator_token(s);
	if (op_len)
		return (op_len);
		
	if (is_quote(s[0]))
	{
		char quote = s[0];
		int i = 1;
		while (s[i] && s[i] != quote)
			i++;
		if (s[i] == quote)
			return i + 1;
	}
	int i = 0;
	while (s[i] && !is_quote(s[i]) && s[i] != ' ' && !is_operator(s[i]))
		i++;
	return i;
}

static char *token_collect(const char *s, int *offset)
{
    int len = next_chunk_len(s);
    if (len <= 0)
    {
        *offset = -1;
        return NULL;
    }
    char *tmp = ft_alloc(len + 1);
    strncpy(tmp, s, len);
    tmp[len] = '\0';
    *offset = len;
    return tmp;
}

char **lexer_split(const char *s, int **flag_array)
{
	int count;
	int i;
	int k;
	int m;
	int offset;
	char **result;
	int	lookahead;
	int	flag;

	flag = 0;
	count = 0;
	i = 0;
	k = 0;
	m = 0;

	// İlk pass: kaç token var say
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break;
		offset = 0;
		token_collect(&s[i], &offset);
		if (offset < 0)
			return (NULL);
		count++;
		i += offset;
	}
	result = ft_alloc(sizeof(char *) * (count + 1));
	*flag_array = ft_alloc(sizeof(int) * count);
	i = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break;
		offset = 0;
		result[k] = token_collect(&s[i], &offset);
		flag = 0;
		lookahead = i + offset;
		if (lookahead < (int)ft_strlen(s) && s[lookahead] != ' ' && !is_operator(s[lookahead]))
			flag = 1;
		(*flag_array)[k] = flag;
		k++;
		if (offset < 0)
		{
			while (m < k -1)
				free(result[m++]);
			free(result);
			return NULL;
		}
		i += offset;
	}
	result[k] = NULL;
	return result;
}

