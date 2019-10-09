/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 17:38:34 by jandreu           #+#    #+#             */
/*   Updated: 2015/04/23 16:36:58 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	char			*s1;
	int				i;
	unsigned int	cpt;

	ptr = (char*)malloc(sizeof(char) * (len + 1));
	i = 0;
	cpt = 0;
	s1 = (char*)s;
	if (ptr == NULL)
		return (NULL);
	while (s1[start] && cpt < len)
	{
		ptr[i] = s1[start];
		start++;
		i++;
		cpt++;
	}
	ptr[i] = '\0';
	return (ptr);
}
