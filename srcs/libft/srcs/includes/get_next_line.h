/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 13:08:26 by jandreu           #+#    #+#             */
/*   Updated: 2017/12/01 21:15:36 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECT_GET_NEXT_LINE_H
# define PROJECT_GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"

int					get_next_line(int const fd, char **line);

# define BUFF_SIZE 10

#endif
