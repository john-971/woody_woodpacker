/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 19:52:01 by jandreu           #+#    #+#             */
/*   Updated: 2017/12/01 21:32:53 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(char *str, char *to_find)
{
	int	i;

	if (to_find[0] == '\0')
		return (str);
	i = 0;
	while (to_find[i] == str[i] && str[i] != '\0')
	{
		i++;
		if (to_find[i] == '\0')
			return (str);
	}
	if (str[i] == '\0')
		return (NULL);
	return (ft_strstr(str + 1, to_find));
}
