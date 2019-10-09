/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 17:55:30 by jandreu           #+#    #+#             */
/*   Updated: 2014/11/27 14:09:07 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char *ptr;

	ptr = (char*)malloc(sizeof(char) * (size + 1));
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, size + 1);
	return (ptr);
}
