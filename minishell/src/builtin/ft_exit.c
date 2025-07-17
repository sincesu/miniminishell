/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:53:24 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/17 20:50:02 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../../Libft/libft.h"
#include "../../include/minishell.h"
#include <stdio.h>

static int	ft_check_param(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i] && is_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0' || !ft_isdigit(str[i]))
		return (1);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && is_whitespace(str[i]))
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

int	exit_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	while (str[i] && is_whitespace(str[i]))
		i++;
	return (sign * res);
}

void	ft_exit(t_shell *shell)
{
	int	exit_code;

	if (shell->args == NULL || shell->args->next == NULL)
	{
		printf("exit\n");
		safe_abort(shell->exit_code);
		return ;
	}
	if (ft_check_param(shell->args->next->content))
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n",
			shell->args->next->content);
		shell->exit_code = 2;
		safe_abort(shell->exit_code);
		return ;
	}
	if (shell->args->next->next)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	exit_code = exit_atoi(shell->args->next->content);
	printf("exit\n");
	safe_abort(exit_code);
}
