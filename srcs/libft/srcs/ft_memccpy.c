/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 14:25:48 by jandreu           #+#    #+#             */
/*   Updated: 2014/11/20 14:04:27 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*source;

	i = 0;
	source = (unsigned char *)src;
	dest = dst;
	while (i < n)
	{
		dest[i] = source[i];
		if (source[i] == (unsigned char)c)
		{
			return (dest + (i + 1));
		}
		i++;
	}
	return (NULL);
}
