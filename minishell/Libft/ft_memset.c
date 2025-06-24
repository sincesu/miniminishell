/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:11:02 by saincesu          #+#    #+#             */
/*   Updated: 2025/05/17 12:46:49 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*x;

	i = 0;
	x = (unsigned char *)b;
	while (i < len)
	{
		x[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
