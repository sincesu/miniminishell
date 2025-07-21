/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:51:22 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/17 20:38:47 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdio.h>

int	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strncmp(cmd, "echo", 5) == 0
		|| ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0
		|| ft_strncmp(cmd, "env", 4) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0);
}

int	ft_execute_builtin(t_shell *shell, t_parser *parser)
{
	if (ft_strncmp(parser->args[0], "echo", 5) == 0)
		return (ft_echo(parser->args));
	else if (ft_strncmp(parser->args[0], "cd", 3) == 0)
		return (ft_cd(shell, parser));
	else if (ft_strncmp(parser->args[0], "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(parser->args[0], "export", 7) == 0)
		return (ft_export(shell));
	else if (ft_strncmp(parser->args[0], "unset", 6) == 0)
		return (ft_unset(shell));
	else if (ft_strncmp(parser->args[0], "env", 4) == 0)
		return (ft_env(shell));
	else if (ft_strncmp(parser->args[0], "exit", 5) == 0)
		ft_exit(shell);
	return (1);
}
