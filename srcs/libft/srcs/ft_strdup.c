/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 15:53:35 by jandreu           #+#    #+#             */
/*   Updated: 2014/11/14 14:29:53 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

char	*ft_strdup(char const *s1)
{
	char *s2;

	s2 = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (s2 != NULL)
	{
		ft_strcpy(s2, s1);
		return (s2);
	}
	else
		return (NULL);
}
