/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:53:26 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/17 20:39:02 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../Libft/libft.h"
#include "../../include/minishell.h"

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
		perror("PWD: ERROR");
		return (0);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}
