/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 15:28:18 by jandreu           #+#    #+#             */
/*   Updated: 2015/01/08 02:19:16 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *ptr;

	if (alst == NULL)
		return ;
	ptr = *alst;
	while (ptr->next)
	{
		ft_lstdelone(alst, (*del));
		ptr = ptr->next;
	}
	del(ptr->content, ptr->content_size);
	free(ptr);
}
