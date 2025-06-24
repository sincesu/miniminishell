/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:10:56 by saincesu          #+#    #+#             */
/*   Updated: 2025/05/17 12:45:53 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*x;
	size_t			i;

	i = 0;
	x = (unsigned char *)s;
	while (i < n)
	{
		if (x[i] == (unsigned char)c)
			return (x + i);
		i++;
	}
	return (NULL);
}
