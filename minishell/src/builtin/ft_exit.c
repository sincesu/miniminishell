/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:53:24 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/06 20:59:31 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../../Libft/libft.h"
#include "../../include/minishell.h"
#include <stdio.h>
#include <limits.h>

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

static long long	ft_exit_atoll(char *str, char *original)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (result > LLONG_MAX / 10
			|| (result == LLONG_MAX / 10 && (*str - '0') > LLONG_MAX % 10))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(original, 2);
			ft_putendl_fd(": numeric argument required", 2);
			safe_abort(2);
		}
		result = result * 10 + (*str++ - '0');
	}
	return (result * sign);
}

int	operator_control(t_token *args)
{
	int		flag;
	t_token	*tmp;

	flag = 0;
	tmp = args;
	while (tmp)
	{
		if (is_operator(tmp->content[0]))
			flag = 1;
		tmp = tmp->next;
	}
	return (flag);
}

static int	exit_checks(t_shell *shell, t_parser *parsed)
{
	if (shell->args == NULL || shell->args->next == NULL)
	{
		ft_putendl_fd("exit", 2);
		safe_abort(shell->exit_code);
		return (1);
	}
	if (is_operator(parsed->args[1][0]))
		return (1);
	if (!operator_control(shell->args))
		ft_putendl_fd("exit", 2);
	if (ft_check_param(parsed->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(shell->args->next->content, 2);
		ft_putendl_fd(": numeric argument required", 2);
		safe_abort(2);
	}
	if (parsed->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		shell->exit_code = 1;
		return (1);
	}
	return (0);
}

void	ft_exit(t_shell *shell, t_parser *parsed)
{
	if (exit_checks(shell, parsed))
		safe_abort(shell->exit_code);
	shell->exit_code = ft_exit_atoll(parsed->args[1],
			parsed->args[1]);
	safe_abort(shell->exit_code);
}
