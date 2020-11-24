/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:32:09 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/24 14:32:27 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double		min(double a, double b)
{
	if (a > b)
		return (b);
	else
		return (a);
}
