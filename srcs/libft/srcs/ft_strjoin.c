/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 18:09:04 by jandreu           #+#    #+#             */
/*   Updated: 2014/11/25 15:26:38 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*news;
	int		tail;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	tail = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	news = (char *)malloc(sizeof(*news) * (tail + 1));
	if (!news || !s1 || !s2)
		return (NULL);
	ft_strcpy(news, s1);
	ft_strcat(news, s2);
	return (news);
}
