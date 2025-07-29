/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:19:02 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/29 19:19:06 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include <errno.h>
#include <string.h>

void	ft_perror(char *pname, char *target, char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(pname, 2);
	ft_putstr_fd(": ", 2);
	if (target != NULL)
		ft_putstr_fd(target, 2);
	if (err == NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else
		ft_putendl_fd(err, 2);
	errno = 0;
}
