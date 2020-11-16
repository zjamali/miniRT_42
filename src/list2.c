/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:05:14 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/16 18:05:39 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	*ft_lstlast_camera(t_camera *lst)
{
	if (lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
		return (lst);
	}
	return (NULL);
}

void		ft_lstadd_back_camera(t_camera **alst, t_camera *new)
{
	t_camera *temp;

	if (*alst)
	{
		temp = ft_lstlast_camera(*alst);
		temp->next = new;
		new->next = NULL;
		new->prev = temp;
	}
	else
		*alst = new;
}
