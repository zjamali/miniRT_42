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
	/*
	else
	{
		return ( (-1*B - sqrt(delta)) / (2.0*A));
	}*/
	double t;
	double t1 = (-B + sqrt(delta)) / (2 * A);
	double t2 = (-B - sqrt(delta)) / (2 * A);
	if (t1 < 0)
		return (0);

	if (t1 > t2)
		t = t2;
	else
		t = t1;

	return t;
}




double hit_plane(t_ray ray,t_plane *plane)
{
	///////////////////// this the correct
	// P - C | V = 0
	// t = DOT1 (-X,V) / DOT1(D,V) 
	double t;

	t_vector X = vectorsSub(&ray.origin,&plane->coord);
	t_vector V = plane->orientation;
	double DOT2 = vectorsDot(&ray.direction,&V);
	if (DOT2 != 0)
	{
		t_vector x = vectorscal(&V,-1);
		double DOT1 = vectorsDot(&X,&x);
		t = DOT1 / DOT2;
		if (t < 0)
		 	return 0;
		return t;
	}
	return 0;
}
double hit_triangle(t_ray ray,t_triangle *triangle)
{
	double epsilon = 0.0000001;
	t_vector edge1, edge2, h, s, q;
	double a, f, u, v, t;

	edge1 = vectorsSub(&triangle->vectors[1],&triangle->vectors[0]);
	edge2 = vectorsSub(&triangle->vectors[2],&triangle->vectors[0]);
	h = vecttorscross(&ray.direction,&edge2);
	a = vectorsDot(&edge1,&h);
	//printf("a");
	if (a > -epsilon && a < epsilon)
        return 0;    // This ray is parallel to this triangle.
    f = 1.0/a;
	s = vectorsSub(&ray.origin,&triangle->vectors[0]);
	u = vectorsDot(&s,&h);
	u = f * u;
	//printf("u");
	if (u < 0.0 || u > 1.0)
        return 0;
	q = vecttorscross(&s,&edge1);
	v = vectorsDot(&ray.direction,&q);
	v = f * v;
	//printf("v");
	if (v < 0.0 || u + v > 1.0)
        return 0;
    // At this stage we can compute t to find out where the intersection point is on the line.
	t = vectorsDot(&q,&edge2);
	t = f * t;
	if (t > epsilon) // ray intersection
        return t;
    else // This means that there is a line intersection but not a ray intersection.
        return 0;
}


/*
double hit_plane(t_ray ray,t_plane *plane)
{
	// P - C | V = 0
	// t = DOT1 (-X,V) / DOT1(D,V) 
	double t;

	t_vector V = normalize(&plane->orientation);
	double DOT2 = vectorsDot(&ray.direction,&V);
	if (DOT2 != 0.0)
	{
		t_vector X = vectorsSub(&ray.origin,&plane->coord);
		t_vector x = vectorscal(&V,-1);
		double DOT1 = vectorsDot(&X,&x);
		t = DOT1 / DOT2;
		if (t >= 0)
		 	return t;
		return 0;
	}
	return 0;
}

double hit_plane(t_ray ray,t_plane *plane)
{
	// P - C | V = 0
	// t = DOT1 (-X,V) / DOT1(D,V) 
	double t;
	double DOT2 = vectorsDot(&ray.direction,&plane->orientation);
	if (DOT2 != 0)
	{
		t_vector x = vectorsSub(&plane->coord,&ray.origin);
		double DOT1 = vectorsDot(&x,&ray.origin);
		t = DOT1 / DOT2;
		if (t > 0)
		 	return 0;
		return t;
	}
	return 0;
}



double hit_plane(t_ray ray,t_plane *plane)
{
	double a;
	double b;
	double t;
	t_vector oc;

	a = vectorsDot(&plane->orientation,&ray.direction);
	//printf("%f\n",a);
	if (a != 0.0)
	{
		oc =  vectorsSub(&plane->coord,&ray.origin);
		b = vectorsDot(&oc, &plane->orientation);
		t = b/ a;
		//printf("%f\n",b);
		if (t > 0.0)
			return (t);
	}
	return 0;
}
*/