/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:01:20 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/24 17:53:52 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_triangle_variables	ft_calcule_triangle(t_ray ray, t_triangle *triangle)
{
	t_triangle_variables tr;

	tr.epsilon = 0.0000001;
	tr.edge1 = vectorssub(triangle->vectors[1], triangle->vectors[0]);
	tr.edge2 = vectorssub(triangle->vectors[2], triangle->vectors[0]);
	tr.h = vecttorscross(ray.direction, tr.edge2);
	tr.a = vectorsdot(tr.edge1, tr.h);
	return (tr);
}

double					hit_triangle(t_ray ray, t_triangle *triangle)
{
	t_triangle_variables	tr;

	tr = ft_calcule_triangle(ray, triangle);
	if (tr.a > -tr.epsilon && tr.a < tr.epsilon)
		return (0);
	tr.f = 1.0 / tr.a;
	tr.s = vectorssub(ray.origin, triangle->vectors[0]);
	tr.u = vectorsdot(tr.s, tr.h);
	tr.u = tr.f * tr.u;
	if (tr.u < 0.0 || tr.u > 1.0)
		return (0);
	tr.q = vecttorscross(tr.s, tr.edge1);
	tr.v = vectorsdot(ray.direction, tr.q);
	tr.v = tr.f * tr.v;
	if (tr.v < 0.0 || tr.u + tr.v > 1.0)
		return (0);
	tr.t = vectorsdot(tr.q, tr.edge2);
	tr.t = tr.f * tr.t;
	if (tr.t > tr.epsilon)
		return (tr.t);
	else
		return (0);
}

t_cylinder_variables	ft_calcule_cylinder_var(t_ray ray, t_cylinder *cylinder)
{
	t_cylinder_variables	cy;

	cy.oc = vectorssub(ray.origin, cylinder->coord);
	cy.a = vectorsdot(ray.direction, ray.direction) -
				(vectorsdot(ray.direction, cylinder->normal) *
					vectorsdot(ray.direction, cylinder->normal));
	cy.b = 2 * (vectorsdot(ray.direction, cy.oc) -
				(vectorsdot(ray.direction, cylinder->normal) *
					vectorsdot(cy.oc, cylinder->normal)));
	cy.c = vectorsdot(cy.oc, cy.oc) -
		vectorsdot(cy.oc, cylinder->normal) * vectorsdot(cy.oc,
			cylinder->normal)
		- (cylinder->diameter / 2) * (cylinder->diameter / 2);
	return (cy);
}

double					hit_cylinder(t_ray ray, t_cylinder *cylinder)
{
	t_cylinder_variables	cy;

	cylinder->normal = normalize(cylinder->normal);
	cy = ft_calcule_cylinder_var(ray, cylinder);
	cy.delta = cy.b * cy.b - 4 * cy.a * cy.c;
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
	cy.min = vectorsdot(ray.direction, cylinder->normal) * cy.t2 +
			vectorsdot(cy.oc, cylinder->normal);
	cy.max = vectorsdot(ray.direction, cylinder->normal) * cy.t1 +
			vectorsdot(cy.oc, cylinder->normal);
	if (cy.min >= 0 && cy.min <= cylinder->height)
		return (cy.t2);
	if (cy.max >= 0 && cy.max <= cylinder->height)
		return (cy.t1);
	return (0);
}
