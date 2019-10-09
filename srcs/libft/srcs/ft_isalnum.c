/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 16:08:49 by jandreu           #+#    #+#             */
/*   Updated: 2014/11/16 16:30:01 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_isalnum(int c)
{
	int	a;
	int	b;

	a = ft_isdigit(c);
	b = ft_isalpha(c);
	if (a == 1 || b == 1)
		return (1);
	else
		return (0);
}
