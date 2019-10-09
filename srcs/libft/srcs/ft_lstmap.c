/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/14 15:28:39 by jandreu           #+#    #+#             */
/*   Updated: 2015/01/08 01:59:09 by jandreu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list*temp;

	if (lst != NULL && *f)
	{
		temp = (*f)(lst);
		if (temp && lst->next)
			temp->next = ft_lstmap(lst->next, f);
		return (temp);
	}
	return (NULL);
}
