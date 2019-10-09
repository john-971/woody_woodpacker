/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 19:53:59 by jandreu           #+#    #+#             */
/*   Updated: 2014/12/06 15:50:02 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t nb;

	i = 0;
	nb = 1;
	if (n == 0)
		return (0);
	while ((unsigned char)s1[i] && (unsigned char)s2[i] && nb < n)
	{
		if ((unsigned char)s1[i] == (unsigned char)s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		nb++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
