/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:49:06 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/07 18:58:03 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"
#include "../../include/minishell.h"

static char	*fill_dolar(char *input, char **env, int var_len)
{
	int		i;
	char	*env_val;
	char	*str;

	env_val = NULL;
	str = NULL;
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
		return (ft_strdup(env_val));
	else
		return (ft_strdup(""));
}

static int	handle_var_expand(char *s, char **env, char **expanded)
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

int	handle_dollar_sequence(char *input, char **expanded, char **env,
		int exit_code)
{
	char	*exit;
	int		i;

	if (input[1] == '?')
	{
		exit = ft_itoa(exit_code);
		*expanded = ft_strjoin(*expanded, exit);
		return (2);
	}
	else if (ft_isalnum(input[1]) || input[1] == '_')
	{
		i = handle_var_expand(input, env, expanded);
		return (i);
	}
	else
	{
		i = handle_normal_char(input, expanded);
		return (i);
	}
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
