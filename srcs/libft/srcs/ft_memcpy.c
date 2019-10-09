/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 12:58:04 by jandreu           #+#    #+#             */
/*   Updated: 2017/12/01 21:05:03 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*ret;
	char	*c_src;

	i = 0;
	ret = dst;
	c_src = (char *)src;
	while (i < n)
	{
		ret[i] = c_src[i];
		i++;
	}
	return (ret);
}
