/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 12:19:21 by jandreu           #+#    #+#             */
/*   Updated: 2015/09/06 17:02:44 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_atoi(char const *str)
{
	int	i;
	int	total;
	int	isnega;

	total = 0;
	i = 0;
	isnega = 0;
	while (str[i] == ' ' || (str[i] < 14 && str[i] > 8))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i++] == 45)
			isnega = 1;
	}
	while (ft_isdigit(str[i]))
	{
		total = total * 10 + str[i] - 48;
		i++;
	}
	if (isnega == 1)
		total = total * -1;
	return (total);
}
