/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 17:29:06 by jandreu           #+#    #+#             */
/*   Updated: 2014/11/13 17:42:33 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char *ptr;

	ptr = (void*)malloc(sizeof(*ptr) * size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, size);
	return ((void*)ptr);
}
