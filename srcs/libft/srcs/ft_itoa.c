/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 16:49:26 by jandreu           #+#    #+#             */
/*   Updated: 2015/01/08 02:20:26 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_int_len(int n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n / 10 != 0)
	{
		i++;
		n /= 10;
	}
	i++;
	return (i);
}

static char	*ft_numput(int len, int n)
{
	char	*dest;

	dest = ft_strnew(len);
	if (dest != NULL)
	{
		len--;
		if (n < 0)
		{
			dest[0] = '-';
			n = n * -1;
		}
		while (n / 10 > 0)
		{
			dest[len] = (n % 10) + '0';
			len--;
			n = n / 10;
		}
		dest[len] = (n % 10) + '0';
	}
	return (dest);
}

char		*ft_itoa(int n)
{
	int		len;
	char	*dest;

	len = ft_int_len(n);
	if (n != -2147483648)
		dest = ft_numput(len, n);
	else
	{
		dest = ft_strnew(11);
		if (dest != NULL)
			ft_strcpy(dest, "-2147483648");
	}
	return (dest);
}
