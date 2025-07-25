/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_command_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:53:23 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:22:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

int	ft_count_commands(t_parser *parsed)
{
	int	count;

	count = 0;
	while (parsed)
	{
		count++;
		parsed = parsed->next;
	}
	return (count);
}

int	ft_create_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pipes[i] = ft_alloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_close_all_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
