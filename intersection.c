/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:01:20 by zjamali           #+#    #+#             */
/*   Updated: 2020/03/14 16:14:06 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double hit_sphere(t_ray ray,t_sphere *sphere)
{
	// a*t^2 + b*t +c = 0;
	t_vector oc =  vectorsSub(&ray.origin,&sphere->origin);
	double A = vectorsDot(&ray.direction,&ray.direction);
	double B = 2.0 * vectorsDot(&oc,&ray.direction);
	double C = vectorsDot(&oc,&oc) - sphere->radius*sphere->radius;

	double delta =  B * B - 4 * A * C;
	
	if (delta < 0)
		return 0;
	else
	{
		return ( (-1*B - sqrt(delta)) / (2.0*A));
	}
}

double hit_plane(t_ray ray,t_plane *plane)
{
	// P - C | V = 0
	// t = DOT1 (-X,V) / DOT1(D,V) 
	double t;

	t_vector X = vectorsSub(&ray.origin,&plane->coord);
	t_vector V = plane->orientation;
	double DOT2 = vectorsDot(&ray.direction,&V);
	if (DOT2 != 0)
	{
		t_vector x = vectorscal(&V,-1);
		double DOT1 = vectorsDot(&x,&V);
		t = DOT1 / DOT2;
		if (t < 0)
		 	return 0;
		return t;
	}
	return 0;
}