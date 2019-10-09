/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:23:52 by jandreu           #+#    #+#             */
/*   Updated: 2014/11/08 16:54:04 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*ft_strrchr(char const *s, int c)
{
	int		i;
	char	*ptr;

	ptr = (char *)s;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (ptr + i);
		i--;
	}
	return (NULL);
}
