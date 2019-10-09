/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 13:05:30 by jandreu           #+#    #+#             */
/*   Updated: 2014/12/01 13:59:06 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int							ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	const unsigned char		*ptr1;
	const unsigned char		*ptr2;

	i = 0;
	ptr1 = s1;
	ptr2 = s2;
	while (i < n)
	{
		if (ptr1[i] == ptr2[i])
			i++;
		else
			return ((int)ptr1[i] - (int)ptr2[i]);
	}
	return (0);
}
