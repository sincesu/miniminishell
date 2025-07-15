/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:16:57 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/14 20:24:37 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdlib.h>

int	is_remove_env(char *env_var, t_token *head)
{
	int		name_len;
	t_token	*token;

	name_len = 0;
	token = head;
	while (token)
	{
		name_len = ft_strlen(token->content);
		if (ft_strncmp(env_var, token->content, name_len) == 0
			&& env_var[name_len] == '=')
			return (1);
		token = token->next;
	}
	return (0);
}

char	**copy_env_without_unset(char **env, t_token *head)
{
	int		i;
	int		j;
	int		env_count;
	char	**new_env;

	i = 0;
	j = 0;
	env_count = 0;
	while (env && env[env_count])
		env_count++;
	new_env = ft_alloc(sizeof(char *) * (env_count + 1));
	i = 0;
	while (env && env[i])
	{
		if (!is_remove_env(env[i], head))
		{
			new_env[j] = env[i];
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

void	ft_unset(t_shell *shell)
{
	t_token	*head;
	char	**new_env;

	head = shell->args;
	if (!head || !head->next)
		return ;
	head = head->next;
	new_env = copy_env_without_unset(shell->env, head);
	shell->env = new_env;
}
