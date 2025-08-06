/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 04:00:39 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/05 13:58:36 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	skip_whitespace(char *str)
{
	int	i;

	i = 0;
	while (is_whitespace(str[i]))
		i++;
	return (i);
}

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	is_redirection_type(int type)
{
	return (type == R_OUT || type == R_APPEND
		|| type == R_IN || type == R_HERE);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
