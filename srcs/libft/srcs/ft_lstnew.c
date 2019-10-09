/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 11:12:45 by jandreu           #+#    #+#             */
/*   Updated: 2014/12/25 20:05:40 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *ptr;

	ptr = malloc(sizeof(t_list));
	if (ptr == NULL)
		return (NULL);
	if (content == NULL)
	{
		ptr->content = NULL;
		ptr->content_size = 0;
	}
	else
	{
		ptr->content = (void*)malloc(sizeof(char) * content_size);
		ptr->content_size = content_size;
		ft_memcpy(ptr->content, content, content_size);
		ptr->next = NULL;
	}
	return (ptr);
}
