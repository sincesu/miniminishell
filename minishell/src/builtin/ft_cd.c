/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:53:19 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/17 20:41:27 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void	ft_print_env_error(char *var)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(" not set\n", 2);
}

static char	*ft_resolve_home_path(t_shell *shell, char *path)
{
	char	*home;
	char	*result;

	home = find_dollar("$HOME", shell->env, 0);
	if (home == NULL)
	{
		ft_print_env_error("HOME");
		return (NULL);
	}
	result = ft_strjoin(home, path + 1);
	if (!result)
		return (NULL);
	return (result);
}

static void	ft_change_env_var(t_shell *shell, char *cwd, char *var_name)
{
	char	*env_entry;

	env_entry = ft_strjoin(var_name, cwd);
	handle_export_arg(shell, env_entry);
	free(cwd);
}

static char	*ft_get_target_path(t_shell *shell, char *path)
{
	char	*old_pwd;

	if (path[0] == '~' && path[1] == '/')
		return (ft_resolve_home_path(shell, path));
	else if (path[0] == '-' && path[1] == '\0')
	{
		old_pwd = find_dollar("$OLDPWD", shell->env, 0);
		if (old_pwd == NULL)
		{
			ft_print_env_error("OLDPWD");
			return (NULL);
		}
		ft_putendl_fd(old_pwd, 1);
		return (old_pwd);
	}
	return (path);
}

int	ft_cd(t_shell *shell, t_parser *parser)
{
	char	*target;
	char	*cwd;
	char	*new_cwd;

	target = ft_get_target_path(shell, parser->args[1]);
	if (!target)
		return (1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd: getcwd");
		return (1);
	}
	ft_change_env_var(shell, cwd, "OLDPWD=");
	if (chdir(target) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	new_cwd = getcwd(NULL, 0);
	if (new_cwd)
		ft_change_env_var(shell, new_cwd, "PWD=");
	return (0);
}
