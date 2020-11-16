/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:02:01 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/16 18:04:26 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*ft_lstlast(t_object *lst)
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

void		ft_lstadd_back(t_object **alst, t_object *new)
{
	t_object *temp;

	if (*alst)
	{
		temp = ft_lstlast(*alst);
		temp->next = new;
		new->next = NULL;
	}
	else
		*alst = new;
}

t_light		*ft_lstlast_light(t_light *lst)
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

void		ft_lstadd_back_light(t_light **alst, t_light *new)
{
	t_light *temp;

	if (*alst)
	{
		temp = ft_lstlast_light(*alst);
		temp->next = new;
		new->next = NULL;
	}
	else
		*alst = new;
}
