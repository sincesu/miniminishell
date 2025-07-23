/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 01:18:00 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:22:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"
#include "../../include/minishell.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static int	get_token_len(const char *s)
{
	int		i;
	int		op_len;
	char	quote;

	op_len = is_operator_token(s);
	if (op_len)
		return (op_len);
	i = 0;
	if (is_quote(s[0]))
	{
		quote = s[0];
		i++;
		while (s[i] && s[i] != quote)
			i++;
		if (s[i] == quote)
			i++;
		return (i);
	}
	while (s[i] && !is_quote(s[i]) && s[i] != ' ' && !is_operator(s[i]))
		i++;
	return (i);
}

static char	*token_collect(const char *s, int *word_len)
{
	int		len;
	char	*tmp;

	len = get_token_len(s);
	tmp = ft_alloc(len + 1);
	ft_strlcpy(tmp, s, len + 1);
	*word_len = len;
	return (tmp);
}

static int	count_tokens(const char *s)
{
	int		count;
	int		i;
	int		word_len;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		word_len = 0;
		token_collect(&s[i], &word_len);
		if (word_len <= 0)
			break ;
		count++;
		i += word_len;
	}
	return (count);
}

void	fill_tokens_and_flags(const char *s, char **result, int *flag_array)
{
	int	i;
	int	k;
	int	word_len;
	int	lookahead;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		word_len = 0;
		result[k] = token_collect(&s[i], &word_len);
		if (word_len <= 0)
			break ;
		lookahead = i + word_len;
		flag_array[k] = (lookahead < (int)ft_strlen(s) && s[lookahead] != ' '
				&& !is_operator(s[lookahead]));
		i += word_len;
		k++;
	}
	result[k] = (NULL);
}

char	**lexer_split(const char *s, int **flag_array)
{
	int		count;
	char	**result;

	count = count_tokens(s);
	result = ft_alloc(sizeof(char *) * (count + 1));
	*flag_array = ft_alloc(sizeof(int) * count);
	fill_tokens_and_flags(s, result, *flag_array);
	return (result);
}
