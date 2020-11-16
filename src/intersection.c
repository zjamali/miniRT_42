/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:01:20 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/16 16:49:44 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		hit_sphere(t_ray ray, t_sphere *sphere)
{
	t_sphere_variables sp;

	sp.oc = vectorsSub(ray.origin, sphere->origin);
	sp.a = vectorsDot(ray.direction, ray.direction);
	sp.b = 2.0 * vectorsDot(sp.oc, ray.direction);
	sp.c = vectorsDot(sp.oc, sp.oc) - sphere->radius * sphere->radius;
	sp.delta = sp.b * sp.b - 4 * sp.a * sp.c;
	if (sp.delta < 0)
		return (0);
	sp.t1 = (-sp.b + sqrt(sp.delta)) / (2 * sp.a);
	sp.t2 = (-sp.b - sqrt(sp.delta)) / (2 * sp.a);
	if (sp.t1 > 0 && sp.t2 > 0)
	{
		if (sp.t2 < 0)
			return (0);
		if (sp.t2 > sp.t1)
			sp.t = sp.t1;
		else
			sp.t = sp.t2;
		return (sp.t);
	}
	return (0);
}

double		hit_plane(t_ray ray, t_plane *plane)
{
	t_plane_variables pl;

	pl.x = vectorsSub(ray.origin, plane->coord);
	pl.v = plane->orientation;
	pl.v = normalize(pl.v);
	pl.d = normalize(ray.direction);
	pl.dot2 = vectorsDot(pl.d, pl.v);
	if (pl.dot2 != 0)
	{
		pl.dot1 = vectorsDot(pl.x, pl.v);
		pl.t = -pl.dot1 / pl.dot2;
		if (pl.t < 0)
			return (0);
		return (pl.t);
	}
	return (0);
}

double		hit_triangle(t_ray ray, t_triangle *triangle)
{
	t_triangle_variables	tr;

	tr.epsilon = 0.0000001;
	tr.edge1 = vectorsSub(triangle->vectors[1], triangle->vectors[0]);
	tr.edge2 = vectorsSub(triangle->vectors[2], triangle->vectors[0]);
	tr.h = vecttorscross(ray.direction, tr.edge2);
	tr.a = vectorsDot(tr.edge1, tr.h);
	if (tr.a > -tr.epsilon && tr.a < tr.epsilon)
		return (0);    // This ray is parallel to this triangle.
	tr.f = 1.0 / tr.a;
	tr.s = vectorsSub(ray.origin, triangle->vectors[0]);
	tr.u = vectorsDot(tr.s, tr.h);
	tr.u = tr.f * tr.u;
	if (tr.u < 0.0 || tr.u > 1.0)
		return (0);
	tr.q = vecttorscross(tr.s, tr.edge1);
	tr.v = vectorsDot(ray.direction, tr.q);
	tr.v = tr.f * tr.v;
	if (tr.v < 0.0 || tr.u + tr.v > 1.0)
		return (0);
	// At this stage we can compute t to find out where the intersection point is on the line.
	tr.t = vectorsDot(tr.q, tr.edge2);
	tr.t = tr.f * tr.t;
	if (tr.t > tr.epsilon) // ray intersection
		return (tr.t);
	else // This means that there is a line intersection but not a ray intersection.
		return (0);
}

double		hit_square(t_ray ray, t_square *square)
{
	double				t;
	t_square_variables	sq;

	t = hit_plane(ray, (t_plane*)square);
	if (t >= 0)
	{
		sq.scale_direction_to_p = vectorscal(ray.direction, t);
		sq.p = vectorsadd(ray.origin, sq.scale_direction_to_p);
		sq.u = vectorsSub(sq.p, square->center);
		sq.r = square->edge_size / 2;
		if (fabs(sq.u.x) > sq.r || fabs(sq.u.y) > sq.r || fabs(sq.u.z) > sq.r)
			return (0);
		return (t);
	}
	return (0);

}

double	hit_cylinder(t_ray ray, t_cylinder *cylinder)
{
	t_cylinder_variables cy;

	cylinder->normal = normalize(cylinder->normal);
	cy.oc =  vectorsSub(ray.origin, cylinder->coord);
	cy.a = vectorsDot(ray.direction, ray.direction) - 
		(vectorsDot(ray.direction, cylinder->normal) * vectorsDot(ray.direction, cylinder->normal));
	cy.b = 2 * (vectorsDot(ray.direction,cy.oc) - 
			(vectorsDot(ray.direction, cylinder->normal) * vectorsDot(cy.oc, cylinder->normal)));
	cy.c = vectorsDot(cy.oc,cy.oc) -
		vectorsDot(cy.oc, cylinder->normal) * vectorsDot(cy.oc, cylinder->normal) -
		(cylinder->diameter / 2) * (cylinder->diameter / 2);
	cy.delta =  cy.b * cy.b - 4 * cy.a * cy.c;
	if (cy.delta < 0)
		return (0);
	cy.t1 = (-cy.b + sqrt(cy.delta)) / (2 * cy.a);
	cy.t2 = (-cy.b - sqrt(cy.delta)) / (2 * cy.a);

	if (cy.t1 < 0)
		return (0);
	if (cy.t1 > cy.t2)
		cy.t = cy.t2;
	else
		cy.t = cy.t1;
	//    m = D|V*t + X|V
	double min = vectorsDot(ray.direction, cylinder->normal) * cy.t2 + vectorsDot(cy.oc, cylinder->normal);
	double max = vectorsDot(ray.direction, cylinder->normal) * cy.t1 + vectorsDot(cy.oc, cylinder->normal);
	if (min >= 0 && min <= cylinder->height)
		return (cy.t2);
	if (max >= 0 && max <= cylinder->height)
		return (cy.t1);
	return (0);
}
