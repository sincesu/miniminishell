/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:49:06 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/17 17:19:10 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"
#include "../../include/minishell.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

char	*fill_dolar(char *input, char **env, int var_len)
{
	int		i;
	char	*expanded;
	char	*env_val;
	char	*str;

	env_val = NULL;
	str = NULL;
	expanded = NULL;
	str = ft_substr(input, 0, var_len);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, var_len) == 0 && env[i][var_len] == '=')
		{
			env_val = ft_strchr(env[i], '=') + 1;
			break ;
		}
		i++;
	}
	if (env_val)
		expanded = ft_strjoin(env_val, input + var_len);
	else
		expanded = ft_strdup(input + var_len);
	return (expanded);
}

int	handle_var_expand(char *s, char **env, char **expanded)
{
	int		j;
	int		varlen;
	char	*varval;

	j = 1;
	while (ft_isalnum(s[j]) || s[j] == '_')
		j++;
	varlen = j - 1;
	varval = fill_dolar(s + 1, env, varlen);
	*expanded = ft_strjoin(*expanded, varval);
	return (j);
}

int	handle_normal_char(char *s, char **expanded)
{
	char	*tmp;

	tmp = ft_alloc(2);
	tmp[0] = s[0];
	tmp[1] = '\0';
	*expanded = ft_strjoin(*expanded, tmp);
	return (1);
}
