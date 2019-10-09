/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/01 16:26:29 by jandreu           #+#    #+#             */
/*   Updated: 2015/07/03 13:41:54 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <fcntl.h>

int			ft_count_line(int fd)
{
	int		cpt;
	char	*line;

	cpt = 0;
	line = ft_memalloc(255);
	while (get_next_line(fd, &line))
		cpt++;
	close(fd);
	return (cpt);
}
