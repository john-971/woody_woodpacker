/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 16:37:55 by jandreu           #+#    #+#             */
/*   Updated: 2014/11/25 15:30:23 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncpy(char *dst, char const *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	if (ft_strlen(src) < n)
	{
		i = ft_strlen(src);
		while (i < n)
		{
			dst[i] = '\0';
			i++;
		}
	}
	return (dst);
}
