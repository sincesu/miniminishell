/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:05:46 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/07 19:28:15 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"

static void	export_only_variable_append(t_shell *shell, char *content)
{
	int		i;
	char	**tmp;

	i = 0;
	while (shell->export_only_list && shell->export_only_list[i])
		i++;
	tmp = ft_alloc(sizeof(char *) * (i + 2));
	i = 0;
	while (shell->export_only_list && shell->export_only_list[i])
	{
		tmp[i] = shell->export_only_list[i];
		i++;
	}
	tmp[i] = ft_strdup(content);
	tmp[i + 1] = NULL;
	shell->export_only_list = tmp;
}

static int	bubble_sort_loop(char **arr, int len)
{
	int		i;
	char	*tmp;
	int		sorted;

	sorted = 1;
	i = 0;
	while (i < len - 1)
	{
		if (ft_strncmp(arr[i], arr[i + 1], ft_strlen(arr[i]) + 1) > 0)
		{
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
			sorted = 0;
		}
		i++;
	}
	return (sorted);
}

void	bubble_sort(char **arr)
{
	int		len;
	int		sorted;

	if (!arr)
		return ;
	len = 0;
	while (arr[len])
		len++;
	sorted = 0;
	while (!sorted)
		sorted = bubble_sort_loop(arr, len);
}

static void	add_export_only_variable(t_shell *shell, char *content)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (shell->export_only_list && shell->export_only_list[i])
	{
		if (ft_strncmp(shell->export_only_list[i], content,
				ft_strlen(content) + 1) == 0)
			found = 1;
		i++;
	}
	if (!found)
		export_only_variable_append(shell, content);
}

void	handle_export_arg(t_shell *shell, char *arg)
{
	char	*eq;
	char	*name;
	int		len;
	int		idx;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		len = eq - arg;
		name = ft_alloc(len + 1);
		ft_strlcpy(name, arg, len + 1);
		idx = find_in_env_index(shell->env, name);
		if (idx != -1)
			update_env_value(shell->env, idx, name, eq);
		else
			append_env_variable(shell, arg);
	}
	else
		add_export_only_variable(shell, arg);
}
