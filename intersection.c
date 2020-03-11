/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:01:20 by zjamali           #+#    #+#             */
/*   Updated: 2020/03/11 19:41:10 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double hit_sphere(t_ray ray,t_sphere *s)
{
	// a*t^2 + b*t +c = 0;
	t_vector oc = vectorsSub(&ray.origin , &s->origin) ;
	double a = vectorsDot(&ray.direction,&ray.direction);
	double b = 2.0 * vectorsDot(&oc,&ray.direction);
	double c = vectorsDot(&oc,&oc) - s->radius * s->radius;

	double delta = b*b - 4 * a*c;
	if (delta < 0)
		return (0);
	double t1 = (-b + sqrt(delta) / (2 * a));
	double t2 = (-b - sqrt(delta) / (2 * a));
	if (t2 < 0)
	 	return (0);
	double t = 0;
	if (t1 > t2)
		t = t2;
	else
		t =  t1;
	// printf("  {%f   %f}[%f]   \n",t1,t2,t );
	return t;
}