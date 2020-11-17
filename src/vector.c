/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 01:05:46 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/17 11:00:18 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	bzero_vector(void)
{
	t_vector v3;

	v3.x = 0;
	v3.y = 0;
	v3.z = 0;
	return (v3);
}

double		lenght(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vector	normalize(t_vector v)
{
	double		norme;
	t_vector	result;

	norme = sqrt(lenght(v));
	result.x = v.x / norme;
	result.y = v.y / norme;
	result.z = v.z / norme;
	return (result);
}

t_vector	vectorsproduit(t_vector v1, t_vector v2)
{
	t_vector result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return (result);
}

t_vector	vecttorscross(t_vector v1, t_vector v2)
{
	t_vector result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (result);
}
