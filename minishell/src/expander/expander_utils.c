/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:49:06 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/15 13:53:14 by saincesu         ###   ########.fr       */
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
		expanded = ft_strdup(env_val);
	else
		expanded = ft_strdup("");
	return (expanded);
}
