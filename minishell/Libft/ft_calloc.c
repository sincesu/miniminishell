/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:11:34 by saincesu          #+#    #+#             */
/*   Updated: 2024/10/21 14:11:35 by saincesu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*buffer;

	total = count * size;
	buffer = (void *)malloc(total);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, total);
	return (buffer);
}
