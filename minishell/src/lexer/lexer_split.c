/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 01:18:00 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/29 13:54:58 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"
#include "../../include/minishell.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static int next_chunk_len(const char *s)
{
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
	while (s[i] && !is_quote(s[i]) && s[i] != ' ')
		i++;
	return i;
}

static char *token_collect(const char *s, int *offset)
{
	int start = 0, len = 0, cap = 64;
	char *tmp = ft_alloc(cap);
	tmp[0] = 0;
	while (s[start] && s[start] != ' ')
	{
		int chunk = next_chunk_len(&s[start]);
		if (chunk == -1)
		{
			free(tmp);
			*offset = -1;
			return NULL;
		}
		if (len + chunk + 1 > cap)
		{
			cap *= 2;
			char *newtmp = realloc(tmp, cap);
			if (!newtmp)
			{
				free(tmp);
				return NULL;
			}
			tmp = newtmp;
		}
		strncat(tmp, &s[start], chunk);
		len += chunk;
		start += chunk;
	}
	*offset = start;
	return tmp;
}

char **lexer_split(const char *s)
{
	int count;
	int i;
	int k;
	int m;
	int offset;
	char **result;

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
	i = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break;
		offset = 0;
		result[k++] = token_collect(&s[i], &offset);
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

// // Test main
// int main()
// {
// 	char str1[] = "\"e\"\"c\"'h''o'";
// 	char str2[] = "echo 'zort 'asd''";
// 	char str3[] = "  ab  'cd ef'  \"gh\"ij ";
// 	char **s;
// 	int i;

// 	printf("Test1:\n");
// 	s = lexer_split(str1);
// 	for (i = 0; s[i]; i++) printf("[%s]\n", s[i]);
// 	printf("Test2:\n");
// 	s = lexer_split(str2);
// 	for (i = 0; s[i]; i++) printf("[%s]\n", s[i]);
// 	printf("Test3:\n");
// 	s = lexer_split(str3);
// 	for (i = 0; s[i]; i++) printf("[%s]\n", s[i]);
// }
