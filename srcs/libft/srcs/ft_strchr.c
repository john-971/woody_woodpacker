/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 20:12:50 by jandreu           #+#    #+#             */
/*   Updated: 2014/11/19 18:10:21 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/libft.h"

char		*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != (char)c && s[i])
	{
		i++;
	}
	if (s[i] == (char)c)
		return ((char*)s + i);
	return (NULL);
}
