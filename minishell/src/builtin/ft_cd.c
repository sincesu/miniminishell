/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:53:19 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:22:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static void	ft_chdir_error(char *target)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(target, 2);
	if (errno == EACCES)
		ft_putendl_fd(": Permission denied", 2);
	else if (errno == ENOENT)
		ft_putendl_fd(": No such file or directory", 2);
	else if (errno == ENOTDIR)
		ft_putendl_fd(": Not a directory", 2);
	else
		ft_putendl_fd(": Unknown error", 2);
}

static char	*ft_resolve_home_path(t_shell *shell, char *path)
{
	char	*home;
	char	*result;

	home = find_dollar("$HOME", shell->env, 0);
	if (home == NULL)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd("HOME", 2);
		ft_putstr_fd(" not set\n", 2);
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

static char	*ft_get_target_path(t_shell *shell, t_parser *parsed)
{
	char	*old_pwd;

	if (parsed->args[1] == NULL)
		return (ft_resolve_home_path(shell, "~"));
	if (parsed->args[1][0] == '~' && parsed->args[1][1] == '/')
		return (ft_resolve_home_path(shell, parsed->args[1]));
	else if (parsed->args[1][0] == '-' && parsed->args[1][1] == '\0')
	{
		old_pwd = find_dollar("$OLDPWD", shell->env, 0);
		if (old_pwd == NULL)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd("OLDPWD", 2);
			ft_putstr_fd(" not set\n", 2);
			return (NULL);
		}
		ft_putendl_fd(old_pwd, 1);
		return (old_pwd);
	}
	return (parsed->args[1]);
}

int	ft_cd(t_shell *shell, t_parser *parsed)
{
	char	*target;
	char	*cwd;
	char	*new_cwd;

	target = ft_get_target_path(shell, parsed);
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
		ft_chdir_error(target);
		return (1);
	}
	new_cwd = getcwd(NULL, 0);
	if (new_cwd)
		ft_change_env_var(shell, new_cwd, "PWD=");
	return (0);
}
