/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:53:19 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/25 13:05:09 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	ft_cd(const char *path)
{
	char	*cwd;

	if (path == NULL)
		path = getenv("HOME");
	if (chdir(path) == -1)
	{
		perror("cd");
		return ;
	}
	cwd = (char *)malloc(PATH_MAX);
	if (!cwd)
	{
		perror("malloc");
		return ;
	}
	if (getcwd(cwd, PATH_MAX))
	{}
	else
		perror("getcwd");
	free(cwd);
}
