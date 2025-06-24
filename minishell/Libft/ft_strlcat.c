/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:12:07 by saincesu          #+#    #+#             */
/*   Updated: 2024/10/21 14:12:08 by saincesu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlen(dst);
	len2 = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (len2);
	if (len1 >= dstsize)
		return (dstsize + len2);
	while (i < dstsize - len1 - 1 && src[i] != '\0')
	{
		dst[len1 + i] = src[i];
		i++;
	}
	dst[len1 + i] = '\0';
	return (len1 + len2);
}
