/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:19:10 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:19:10 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

int	is_operator_token(const char *s)
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

int	tokenize(char *str)
{
	int	len;

	if (strcmp(str, ">") == 0)
		return (R_OUT);
	if (strcmp(str, ">>") == 0)
		return (R_APPEND);
	if (strcmp(str, "|") == 0)
		return (PIPE);
	if (strcmp(str, "<") == 0)
		return (R_IN);
	if (strcmp(str, "<<") == 0)
		return (R_HERE);
	len = ft_strlen(str);
	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		return (S_WORD);
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (D_WORD);
	return (U_WORD);
}

t_token	*lexer(char *input)
{
	int		i;
	char	**str;
	int		*flag_array;
	int		tmp_token;
	t_token	*head_list;

	i = 0;
	head_list = NULL;
	flag_array = NULL;
	str = lexer_split(input, &flag_array);
	if (!str)
		return (NULL);
	while (str[i])
	{
		tmp_token = tokenize(str[i]);
		ft_lstadd_back_token(&head_list, ft_lstnew_token((t_token){
				.content = ft_strdup(str[i]), .type = tmp_token,
				.flag = flag_array[i], .next = NULL}));
		i++;
	}
	return (head_list);
}
