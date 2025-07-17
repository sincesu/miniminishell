/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:53:26 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/25 12:53:27 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../Libft/libft.h"
#include "../../include/minishell.h"

void	ft_change_pwd(t_shell *shell, char *cwd)
{
	char	*old_pwd;
	(void)shell;

	old_pwd = ft_strdup("PWD");
	old_pwd = ft_strjoin(old_pwd, "=");
	old_pwd = ft_strjoin(old_pwd, cwd);
	handle_export_arg(shell, cwd);
	free(cwd);
}

int	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("PWD: ERROR");
		return (0);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	ft_change_pwd(shell, pwd);
	return (1);
}
