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
	V = normalize(&V);
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

double hit_square(t_ray ray,t_square *square)
{
	double t;
	double size;
	t_vector e1,e2;

	t = hit_plane(ray,(t_plane*)square);

	if (t >=0)
	{
		t_vector scale_direction_to_p = vectorscal(&ray.direction,t);
		t_vector p = vectorsadd(&ray.origin,&scale_direction_to_p);

		t_vector u = vectorsSub(&p,&square->center);

		double r = square->edge_size/2;

		if (fabs(u.x) > r || fabs(u.y) > r || fabs(u.z) > r)
			return 0;
		return t;
	}
	return 0;
	
}

double hit_cylinder(t_ray ray,t_cylinder *cylinder)
{
	double t = 0;
	// a*t^2 + b*t +c = 0;
	cylinder->normal = normalize(&cylinder->normal);
	t_vector oc =  vectorsSub(&ray.origin,&cylinder->coord);
	double a = vectorsDot(&ray.direction,&ray.direction) - 
				(vectorsDot(&ray.direction,&cylinder->normal) * vectorsDot(&ray.direction,&cylinder->normal));
	double b = 2 * (vectorsDot(&ray.direction,&oc) - 
				(vectorsDot(&ray.direction,&cylinder->normal) * vectorsDot(&oc,&cylinder->normal)));
	double c = vectorsDot(&oc,&oc) -
				vectorsDot(&oc,&cylinder->normal) * vectorsDot(&oc,&cylinder->normal) -
				(cylinder->diameter/2) * (cylinder->diameter/2);
	double delta =  b * b - 4 * a * c;
	
	if (delta < 0)
		return 0;
	double t1 = (-b + sqrt(delta)) / (2 * a);
	double t2 = (-b - sqrt(delta)) / (2 * a);

	if (t1 < 0)
		return (0);
	
	if (t1 > t2)
		t = t2;
	else
		t = t1;
	//    m = D|V*t + X|V
	double min = vectorsDot(&ray.direction,&cylinder->normal) * t2 + vectorsDot(&oc,&cylinder->normal);
	double max = vectorsDot(&ray.direction,&cylinder->normal) * t1 + vectorsDot(&oc,&cylinder->normal);
	if (min >= 0 && min <= cylinder->height)
		return t2;
	if (max >= 0 && max <= cylinder->height)
		return t1;
	return 0;
}

double hit_disk(t_ray ray,t_disk *disk)
{
	///////////////////// this the correct
	// P - C | V = 0
	// t = DOT1 (-X,V) / DOT1(D,V) 
	double t;
	t_vector X = vectorsSub(&ray.origin,&disk->coord);
	t_vector V = disk->orientation;
	V = normalize(&V);
	double DOT2 = vectorsDot(&ray.direction,&V);
	if (DOT2 != 0)
	{
		t_vector x = vectorscal(&V,-1);
		double DOT1 = vectorsDot(&X,&x);
		t = DOT1 / DOT2;
		if (t < 0)
		 	return 0;
		t_vector scale_direction_to_p = vectorscal(&ray.direction,t);
		t_vector p = vectorsadd(&ray.origin,&scale_direction_to_p);
		t_vector op = vectorsSub(&p,&disk->coord);
		double h = vectorsDot(&op,&op);
		if (sqrtf(h) <= disk->radius)
			return t;
	}
	return 0;
}

/*
t_plane cap_0;
	cap_0.color = cylinder->color;
	cap_0.coord = cylinder->coord;
	cap_0.orientation = vectorscal(&cylinder->normal,-1);

	t_plane cap_1;
	cap_1.color = cylinder->color;
	// cap_1.coord.x = cylinder->coord.x + cylinder->height;
	// cap_1.coord.y = cylinder->coord.y + cylinder->height;
	// cap_1.coord.z = cylinder->coord.z + cylinder->height;
	cap_1.coord = vectorscal(&cylinder->normal,cylinder->height);
	cap_1.coord = vectorsadd(&cap_1.coord,&cylinder->coord);
	cap_1.orientation = cylinder->normal;
	t = 0;
	double tp1;
	double tp0;
	double tp;
	tp0 = hit_plane(ray,&cap_0);
	tp1 = hit_plane(ray,&cap_1);
	//////if (t > 0)
	//{
		t_vector scale_direction_to_P0 = vectorscal(&ray.direction,tp0);
		t_vector p0 = vectorsadd(&ray.origin,&scale_direction_to_P0);
		t_vector op0 = vectorsSub(&p0,&cap_0.coord);

		t_vector scale_direction_to_P1 = vectorscal(&ray.direction,tp1);
		t_vector p1 = vectorsadd(&ray.origin,&scale_direction_to_P1);
		t_vector op1 = vectorsSub(&p1,&cap_1.coord);

		if(lenght(&op0) <= cylinder->diameter/2)
		{
			//printf("%f,%f,%f\n",p.x,p.y,p.z);
			if (tp1 > tp0)
				tp = tp0;
		}
		if(lenght(&op1) <= cylinder->diameter/2)
		{
			//printf("%f,%f,%f\n",p.x,p.y,p.z);
			if (tp1 < tp0)
				tp = tp1;
		}
		if (tp < t)
		{
			printf("f ");
			return tp;
		}
		//else if (tp < t && tp > 0)
			//return tp;
		
	//}
	return 0;

*/

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