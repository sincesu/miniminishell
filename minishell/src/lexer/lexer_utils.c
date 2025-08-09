/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 01:18:00 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/06 21:02:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"
#include "../../include/minishell.h"

static int	get_quoted_len(const char *s)
{
	int		i;
	char	quote;

	quote = s[0];
	i = 1;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}

static int	get_token_len(const char *s)
{
	int		i;
	char	quote;

	if (is_operator_token(s))
		return (is_operator_token(s));
	if (is_quote(s[0]))
		return (get_quoted_len(s));
	i = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == quote)
				i++;
		}
		else if (is_whitespace(s[i]) || is_operator(s[i]))
			break ;
		else
			i++;
	}
	return (i);
}

int	count_tokens(const char *s)
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
		word_len = get_token_len(&s[i]);
		count++;
		i += word_len;
	}
	return (count);
}

static int	set_flag_and_token(const char *s, char **res, int *flags)
{
	int	len;
	int	lookahead;

	len = get_token_len(s);
	if (len <= 0)
		return (0);
	*res = ft_alloc(len + 1);
	ft_strlcpy(*res, s, len + 1);
	lookahead = len;
	if (is_operator_token(*res))
		*flags = 0;
	else
		*flags = (s[lookahead] && s[lookahead] != ' '
				&& !is_operator(s[lookahead]));
	return (len);
}

void	fill_tokens_and_flags(const char *s, char **res, int *flags)
{
	int	i;
	int	k;
	int	len;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		len = set_flag_and_token(&s[i], &res[k], &flags[k]);
		if (len == 0)
			break ;
		i += len;
		k++;
	}
	res[k] = NULL;
}
