/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:01:20 by zjamali           #+#    #+#             */
/*   Updated: 2020/10/30 11:41:12 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*
double hit_sphere(t_ray ray,t_sphere *sphere)
{
	t_sphere_variables sp;
	// a*t^2 + b*t +c = 0;
	//printf("%f\n",sphere->origin.x);
	sp.oc =  vectorsSub(&ray.origin,&sphere->origin);
	sp.a = vectorsDot(&ray.direction,&ray.direction);
	sp.b = 2.0 * vectorsDot(&sp.oc,&ray.direction);
	sp.c = vectorsDot(&sp.oc,&sp.oc) - sphere->radius*sphere->radius;

	sp.delta =  sp.b * sp.b - 4 * sp.a * sp.c;
	
	if (sp.delta < 0)
		return 0;
	sp.t1 = (-sp.b + sqrt(sp.delta)) / (2 * sp.a);
	sp.t2 = (-sp.b - sqrt(sp.delta)) / (2 * sp.a);

	if (sp.t1 > 0 && sp.t2 > 0)
	{
		if (sp.t2 < 0)
			return 0;
		if (sp.t2 > sp.t1)
			sp.t = sp.t1;
		else
			sp.t = sp.t2;
		return sp.t;
	}
	return 0;
}
*/
double hit_sphere(t_ray ray,t_object *sphere)
{
	t_sphere_variables sp;
	// a*t^2 + b*t +c = 0;
	//printf("%f\n",sphere->origin.x);
	sp.oc =  vectorsSub(&ray.origin,&sphere->origin);
	sp.a = vectorsDot(&ray.direction,&ray.direction);
	sp.b = 2.0 * vectorsDot(&sp.oc,&ray.direction);
	sp.c = vectorsDot(&sp.oc,&sp.oc) - sphere->radius*sphere->radius;

	sp.delta =  sp.b * sp.b - 4 * sp.a * sp.c;
	
	if (sp.delta < 0)
		return 0;
	sp.t1 = (-sp.b + sqrt(sp.delta)) / (2 * sp.a);
	sp.t2 = (-sp.b - sqrt(sp.delta)) / (2 * sp.a);

	if (sp.t1 > 0 && sp.t2 > 0)
	{
		if (sp.t2 < 0)
			return 0;
		if (sp.t2 > sp.t1)
			sp.t = sp.t1;
		else
			sp.t = sp.t2;
		return sp.t;
	}
	return 0;
}

double hit_plane(t_ray ray,t_plane *plane)
{
	//printf("%f,%f,%f\n",plane->coord.x,plane->coord.y,plane->coord.z);
	///////////////////// this the correct
	// P - C | V = 0
	// t = DOT1 (-X,V) / DOT1(D,V) 

	t_plane_variables pl;
	
	pl.x = vectorsSub(&ray.origin,&plane->coord);
	pl.v = plane->orientation;
	pl.v = normalize(&pl.v);

	pl.d = normalize(&ray.direction);
	pl.dot2 = vectorsDot(&pl.d,&pl.v);
	if (pl.dot2 != 0)
	{
		//t_vector x = vectorscal(&V,-1);
		//double DOT1 = vectorsDot(&X,&x);
		//X = normalize(&X);
		pl.dot1 = vectorsDot(&pl.x,&pl.v);
		pl.t = -pl.dot1 / pl.dot2;
		if (pl.t < 0)
		 	return 0;
		return pl.t;
	}
	return 0;
}

/*
double hit_plane(t_ray ray,t_object *plane)
{
	//printf("%f,%f,%f\n",plane->coord.x,plane->coord.y,plane->coord.z);
	///////////////////// this the correct
	// P - C | V = 0
	// t = DOT1 (-X,V) / DOT1(D,V) 

	t_plane_variables pl;
	
	pl.x = vectorsSub(&ray.origin,&plane->origin);
	pl.v = plane->orientation;
	printf("%f|%f|%f\n",plane->orientation.x,plane->orientation.y,plane->orientation.z);
	pl.v = normalize(&pl.v);

	pl.d = normalize(&ray.direction);
	pl.dot2 = vectorsDot(&pl.d,&pl.v);
	if (pl.dot2 != 0)
	{
		//t_vector x = vectorscal(&V,-1);
		//double DOT1 = vectorsDot(&X,&x);
		//X = normalize(&X);
		pl.dot1 = vectorsDot(&pl.x,&pl.v);
		pl.t = -pl.dot1 / pl.dot2;
		if (pl.t < 0)
		 	return 0;
		return pl.t;
	}
	return 0;
}
*/
double hit_triangle(t_ray ray,t_triangle *triangle)
{
	t_triangle_variables tr;
	//double epsilon = 0.0000001;
	//t_vector edge1, edge2, h, s, q;
	//double a, f, u, v, t;

	tr.epsilon = 0.0000001;

	tr.edge1 = vectorsSub(&triangle->vectors[1],&triangle->vectors[0]);
	tr.edge2 = vectorsSub(&triangle->vectors[2],&triangle->vectors[0]);
	tr.h = vecttorscross(&ray.direction,&tr.edge2);
	tr.a = vectorsDot(&tr.edge1,&tr.h);
	//printf("a");
	if (tr.a > -tr.epsilon && tr.a < tr.epsilon)
        return 0;    // This ray is parallel to this triangle.
    tr.f = 1.0/tr.a;
	tr.s = vectorsSub(&ray.origin,&triangle->vectors[0]);
	tr.u = vectorsDot(&tr.s,&tr.h);
	tr.u = tr.f * tr.u;
	if (tr.u < 0.0 || tr.u > 1.0)
        return 0;
	tr.q = vecttorscross(&tr.s,&tr.edge1);
	tr.v = vectorsDot(&ray.direction,&tr.q);
	tr.v = tr.f * tr.v;
	if (tr.v < 0.0 || tr.u + tr.v > 1.0)
        return 0;
    // At this stage we can compute t to find out where the intersection point is on the line.
	tr.t = vectorsDot(&tr.q,&tr.edge2);
	tr.t = tr.f * tr.t;
	if (tr.t > tr.epsilon) // ray intersection
        return tr.t;
    else // This means that there is a line intersection but not a ray intersection.
        return 0;
}
/*
double hit_square(t_ray ray,t_square *square)
{
	double t;
	//double size;
	//t_vector e1,e2;
	t_square_variables sq;
	
	t = hit_plane(ray,(t_plane*)square);

	if (t >=0)
	{
		sq.scale_direction_to_p = vectorscal(&ray.direction,t);
		sq.p = vectorsadd(&ray.origin,&sq.scale_direction_to_p);

		sq.u = vectorsSub(&sq.p,&square->center);

		sq.r = square->edge_size/2;

		if (fabs(sq.u.x) > sq.r || fabs(sq.u.y) > sq.r || fabs(sq.u.z) > sq.r)
			return 0;
		return t;
	}
	return 0;
	
}
*/

double hit_square(t_ray ray,t_square *square)
{
	double t;
	//double size;
	//t_vector e1,e2;
	t_square_variables sq;
	
	t = hit_plane(ray,(t_plane*)square);

	if (t >=0)
	{
		sq.scale_direction_to_p = vectorscal(&ray.direction,t);
		sq.p = vectorsadd(&ray.origin,&sq.scale_direction_to_p);

		sq.u = vectorsSub(&sq.p,&square->center);

		sq.r = square->edge_size/2;

		if (fabs(sq.u.x) > sq.r || fabs(sq.u.y) > sq.r || fabs(sq.u.z) > sq.r)
			return 0;
		return t;
	}
	return 0;
	
}
/*
double hit_cylinder(t_ray ray,t_cylinder *cylinder)
{
	t_cylinder_variables cy;
	
	//double t = 0;
	// a*t^2 + b*t +c = 0;
	cylinder->normal = normalize(&cylinder->normal);
	cy.oc =  vectorsSub(&ray.origin,&cylinder->coord);
	cy.a = vectorsDot(&ray.direction,&ray.direction) - 
				(vectorsDot(&ray.direction,&cylinder->normal) * vectorsDot(&ray.direction,&cylinder->normal));
	cy.b = 2 * (vectorsDot(&ray.direction,&cy.oc) - 
				(vectorsDot(&ray.direction,&cylinder->normal) * vectorsDot(&cy.oc,&cylinder->normal)));
	cy.c = vectorsDot(&cy.oc,&cy.oc) -
				vectorsDot(&cy.oc,&cylinder->normal) * vectorsDot(&cy.oc,&cylinder->normal) -
				(cylinder->diameter / 2) * (cylinder->diameter / 2);
	cy.delta =  cy.b * cy.b - 4 * cy.a * cy.c;
	
	if (cy.delta < 0)
		return 0;
	cy.t1 = (-cy.b + sqrt(cy.delta)) / (2 * cy.a);
	cy.t2 = (-cy.b - sqrt(cy.delta)) / (2 * cy.a);

	if (cy.t1 < 0)
		return (0);
	
	if (cy.t1 > cy.t2)
		cy.t = cy.t2;
	else
		cy.t = cy.t1;
	//    m = D|V*t + X|V
	double min = vectorsDot(&ray.direction,&cylinder->normal) * cy.t2 + vectorsDot(&cy.oc,&cylinder->normal);
	double max = vectorsDot(&ray.direction,&cylinder->normal) * cy.t1 + vectorsDot(&cy.oc,&cylinder->normal);
	if (min >= 0 && min <= cylinder->height)
		return cy.t2;
	if (max >= 0 && max <= cylinder->height)
		return cy.t1;
	return 0;
}
*/
double hit_cylinder(t_ray ray,t_object *cylinder)
{
	t_cylinder_variables cy;
	
	//double t = 0;
	// a*t^2 + b*t +c = 0;
	cylinder->orientation = normalize(&cylinder->orientation);
	cy.oc =  vectorsSub(&ray.origin,&cylinder->origin);
	cy.a = vectorsDot(&ray.direction,&ray.direction) - 
				(vectorsDot(&ray.direction,&cylinder->orientation) * vectorsDot(&ray.direction,&cylinder->orientation));
	cy.b = 2 * (vectorsDot(&ray.direction,&cy.oc) - 
				(vectorsDot(&ray.direction,&cylinder->orientation) * vectorsDot(&cy.oc,&cylinder->orientation)));
	cy.c = vectorsDot(&cy.oc,&cy.oc) -
				vectorsDot(&cy.oc,&cylinder->orientation) * vectorsDot(&cy.oc,&cylinder->orientation) -
				(cylinder->diameter / 2) * (cylinder->diameter / 2);
	cy.delta =  cy.b * cy.b - 4 * cy.a * cy.c;
	
	if (cy.delta < 0)
		return 0;
	cy.t1 = (-cy.b + sqrt(cy.delta)) / (2 * cy.a);
	cy.t2 = (-cy.b - sqrt(cy.delta)) / (2 * cy.a);

	if (cy.t1 < 0)
		return (0);
	
	if (cy.t1 > cy.t2)
		cy.t = cy.t2;
	else
		cy.t = cy.t1;
	//    m = D|V*t + X|V
	double min = vectorsDot(&ray.direction,&cylinder->orientation) * cy.t2 + vectorsDot(&cy.oc,&cylinder->orientation);
	double max = vectorsDot(&ray.direction,&cylinder->orientation) * cy.t1 + vectorsDot(&cy.oc,&cylinder->orientation);
	if (min >= 0 && min <= cylinder->size)
		return cy.t2;
	if (max >= 0 && max <= cylinder->size)
		return cy.t1;
	return 0;
}

double hit_disk(t_ray ray,t_disk *disk)
{
	///////////////////// this the correct
	// P - C | V = 0
	// t = DOT1 (-X,V) / DOT1(D,V) 
	t_disk_variables dsk;
	t_vector x;
	dsk.x = vectorsSub(&ray.origin,&disk->coord);
	dsk.v = disk->orientation;
	dsk.v = normalize(&dsk.v);
	dsk.dot2 = vectorsDot(&ray.direction,&dsk.v);
	if (dsk.dot2 != 0)
	{
		x = vectorscal(&dsk.v,-1);
		dsk.dot1 = vectorsDot(&dsk.x,&x);
		dsk.t = dsk.dot1 / dsk.dot2;
		if (dsk.t < 0)
		 	return 0;
		dsk.scale_direction_to_p = vectorscal(&ray.direction,dsk.t);
		dsk.p = vectorsadd(&ray.origin,&dsk.scale_direction_to_p);
		dsk.op = vectorsSub(&dsk.p,&disk->coord);
		dsk.h = vectorsDot(&dsk.op,&dsk.op);
		if (sqrtf(dsk.h) <= disk->radius)
			return dsk.t;
	}
	return 0;
}