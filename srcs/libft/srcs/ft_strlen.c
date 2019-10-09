/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 13:34:40 by jandreu           #+#    #+#             */
/*   Updated: 2014/11/04 19:16:38 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/libft.h"

size_t	ft_strlen(char const *c)
{
	int cpt;

	cpt = 0;
	while (c[cpt])
		cpt++;
	return (cpt);
}
