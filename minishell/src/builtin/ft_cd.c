/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:53:19 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/29 13:55:35 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../Libft/libft.h"
#include "../../include/minishell.h"

char	*ft_handle_home_path(const char *path)
{
	char	*home;
	char	*target;
	size_t	len;
	size_t	i;

	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (NULL);
	}
	if (!path || path[0] == '\0' || (path[0] == '~' && path[1] == '\0'))
		return (home);
	len = ft_strlen(home) + ft_strlen(path + 1) + 1;
	target = malloc(len);
	if (!target)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while (home[i])
	{
		target[i] = home[i];
		i++;
	}
	while (path[++i - ft_strlen(home)])
		target[i - 1] = path[i - ft_strlen(home)];
	target[i - 1] = '\0';
	return (target);
}

char	*ft_handle_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = getenv("OLDPWD");
	if (!oldpwd)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (NULL);
	}
	ft_putstr_fd(oldpwd, 1);
	ft_putchar_fd('\n', 1);
	return (oldpwd);
}

void	ft_change_oldpwd(t_shell *shell, char *cwd)
{
	char	*old_pwd;
	(void)shell;

	old_pwd = ft_strdup("OLDPWD");
	old_pwd = ft_strjoin(old_pwd, "=");
	old_pwd = ft_strjoin(old_pwd, cwd);
	handle_export_arg(shell, cwd);
	free(cwd);
}

char	*ft_get_target_path(const char *path, int *needs_free)
{
	if (!path || path[0] == '\0' || (path[0] == '~' && path[1] == '\0'))
		return (ft_handle_home_path(path));
	else if (path[0] == '-' && path[1] == '\0')
		return (ft_handle_oldpwd());
	else if (path[0] == '~' && path[1] == '/')
	{
		*needs_free = 1;
		return (ft_handle_home_path(path));
	}
	return ((char *)path);
}

int	ft_cd(t_shell *shell, t_parser *parser)
{
	char	*target;
	char	*cwd;
	int		needs_free;

	(void)shell;
	needs_free = 0;
	target = ft_get_target_path(parser->args[1], &needs_free);
	if (!target)
		return (500);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		if (needs_free)
			free(target);
		return (500);
	}
	ft_change_oldpwd(shell, cwd);
	if (chdir(target) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
		perror("");
	}
	if (needs_free)
		free(target);
	return (0);
}
