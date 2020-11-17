/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 09:40:32 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/17 10:11:33 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		hit_square(t_ray ray, t_square *square)
{
	double				t;
	t_square_variables	sq;

	t = hit_plane(ray, (t_plane*)square);
	if (t >= 0)
	{
		sq.scale_direction_to_p = vectorscal(ray.direction, t);
		sq.p = vectorsadd(ray.origin, sq.scale_direction_to_p);
		sq.u = vectorssub(sq.p, square->center);
		sq.r = square->edge_size / 2;
		if (fabs(sq.u.x) > sq.r || fabs(sq.u.y) > sq.r || fabs(sq.u.z) > sq.r)
			return (0);
		return (t);
	}
	return (0);
}

double		hit_plane(t_ray ray, t_plane *plane)
{
	t_plane_variables pl;

	pl.x = vectorssub(ray.origin, plane->coord);
	pl.v = plane->orientation;
	pl.v = normalize(pl.v);
	pl.d = normalize(ray.direction);
	pl.dot2 = vectorsdot(pl.d, pl.v);
	if (pl.dot2 != 0)
	{
		pl.dot1 = vectorsdot(pl.x, pl.v);
		pl.t = -pl.dot1 / pl.dot2;
		if (pl.t < 0)
			return (0);
		return (pl.t);
	}
	return (0);
}

double		hit_sphere(t_ray ray, t_sphere *sphere)
{
	t_sphere_variables sp;

	sp.oc = vectorssub(ray.origin, sphere->origin);
	sp.a = vectorsdot(ray.direction, ray.direction);
	sp.b = 2.0 * vectorsdot(sp.oc, ray.direction);
	sp.c = vectorsdot(sp.oc, sp.oc) - sphere->radius * sphere->radius;
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
