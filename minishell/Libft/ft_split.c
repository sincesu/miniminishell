/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:04:27 by saincesu          #+#    #+#             */
/*   Updated: 2024/10/26 14:04:27 by saincesu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/minishell.h"
#include <stdlib.h>

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	if (!s[i])
		return (0);
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		x;
	char	**split;

	if (!s)
		return (NULL);
	x = ft_wordcount(s, c);
	i = 0;
	j = 0;
	split = (char **)ft_alloc(sizeof(char *) * (x + 1));
	while (i < x)
	{
		while (s[j] == c)
			j++;
		split[i] = ft_substr(s, j, ft_wordlen(&s[j], c));
		j += ft_wordlen(&s[j], c);
		i++;
	}
	split[i] = NULL;
	return (split);
}
