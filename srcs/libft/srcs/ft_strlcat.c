/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 18:06:26 by jandreu           #+#    #+#             */
/*   Updated: 2014/11/25 15:39:02 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../includes/libft.h"

size_t		ft_strlcat(char *dst, char const *src, size_t size)
{
	size_t	i;
	int		j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(dst) + ft_strlen(src);
	while (dst[i] != '\0' && i < size)
		i++;
	if (i == size)
		return (ft_strlen(src) + size);
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (len);
}
