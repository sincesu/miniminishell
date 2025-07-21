/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:53:21 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/25 12:53:22 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"

static int	ft_is_n_option(char *arg)
{
	if (!arg || arg[0] != '-')
		return (0);
	arg++;
	while (*arg)
	{
		if (*arg != 'n')
			return (0);
		arg++;
	}
	return (1);
}

static void	ft_print_args(char **args, int i, int n_option)
{
	int	first;

	if (!args)
		return ;
	first = 1;
	while (args[i])
	{
		if (!first)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(args[i], 1);
		first = 0;
		i++;
	}
	if (!n_option)
		ft_putchar_fd('\n', 1);
}

int	ft_echo(char **args)
{
	int	i;
	int	n_option;

	if (!args)
		return (0);
	if (!args[1])
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	i = 1;
	n_option = 0;
	while (args[i] && ft_is_n_option(args[i]))
	{
		n_option = 1;
		i++;
	}
	ft_print_args(args, i, n_option);
	return (0);
}
