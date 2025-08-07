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

#include "../../Libft/libft.h"
#include "../../include/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static int	ft_error_pwd(char c)
{
	ft_putstr_fd("minishell: pwd: -", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd(": invalid option", 2);
	return (2);
}

int	ft_pwd(char **parsed)
{
	char	*pwd;

	if (parsed[1] && parsed[1][0] == '-')
		return (ft_error_pwd(parsed[1][1]));
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_perror("pwd", NULL, NULL);
		return (0);
	}
	signal(SIGPIPE, SIG_IGN);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}
