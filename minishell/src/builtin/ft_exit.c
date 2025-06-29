/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:53:24 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/29 14:07:30 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../../Libft/libft.h"
#include "../../include/minishell.h"
#include <stdio.h>

void	ft_exit(char *arg, t_shell *shell)
{
	int	exit_code;

	if (arg == NULL)
	{
		printf("exit\n");
		safe_abort(shell->exit_code);
	}
	exit_code = ft_atoi(arg);
	printf("exit\n");
	safe_abort(exit_code);
}
