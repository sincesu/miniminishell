/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:13:03 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/29 17:37:23 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/minishell.h"
#include <stdlib.h>

char	*ft_strdup(const char *str)
{
	int		i;
	char	*s1;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	s1 = ft_alloc(len + 1);
	while (str[i])
	{
		s1[i] = str[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
