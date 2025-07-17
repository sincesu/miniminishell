/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:53:26 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/17 20:09:20 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../Libft/libft.h"
#include "../../include/minishell.h"

int	ft_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("PWD: ERROR");
		return (0);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (1);
}
