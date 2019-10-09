/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 18:10:20 by jandreu           #+#    #+#             */
/*   Updated: 2014/11/17 18:12:48 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*ptr;
	int		i;
	int		len;

	if (!s || !f)
		return (NULL);
	len = ft_strlen((char *)s);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = (*f)(s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
