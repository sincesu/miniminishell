/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:53:19 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/29 13:55:35 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../../include/minishell.h"

void	ft_cd(const char *path)
{
	//char	*cwd;

	if (path == NULL)
		path = getenv("HOME");
	if (chdir(path) == -1)
	{
		perror("cd");
		return ;
	}
	// cwd = ft_alloc(4096);
	// if (!cwd)
	// {
	// 	perror("malloc");
	// 	return ;
	// }
	// if (getcwd(cwd, 4096))
	// {}
	// else
	// 	perror("getcwd");
	// free(cwd);
}
