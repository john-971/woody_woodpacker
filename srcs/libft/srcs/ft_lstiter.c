/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 16:21:48 by jandreu           #+#    #+#             */
/*   Updated: 2015/01/08 02:00:38 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *ptr;

	if (lst == NULL)
		return ;
	ptr = lst;
	while (ptr)
	{
		(f)(ptr->content);
		ptr = ptr->next;
	}
}
