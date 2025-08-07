/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:53:26 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:22:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../Libft/libft.h"
#include "../../include/minishell.h"
#include <signal.h>

int	ft_pwd(t_shell *shell)
{
	char	*pwd;

	if (shell->args->next && shell->args->next->type == U_WORD)
	{
		if (shell->args->next->content[0] == '-')
		{
			ft_putstr_fd("minishell: pwd: -", 2);
			ft_putchar_fd(shell->args->next->content[1], 2);
			ft_putendl_fd(": invalid option", 2);
			return (2);
		}
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_perror("pwd", NULL, NULL);
		return (0);
	}
	if (g_signal_received == SIGPIPE)
	{
		free(pwd);
		g_signal_received = 0;
		return (0);
	}	
	else
		ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}
