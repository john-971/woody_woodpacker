/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 15:01:32 by jandreu           #+#    #+#             */
/*   Updated: 2014/11/14 17:30:05 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <string.h>

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int i;

	i = ft_strncmp(s1, s2, n);
	if (i == 0)
		return (1);
	return (0);
}
