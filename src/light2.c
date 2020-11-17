/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:34:23 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/17 09:31:38 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	ft_ambient(t_ambient ambient, t_vector *color)
{
	t_vector i_ambient;

	i_ambient.x = ambient.intensity * color->x / 255;
	i_ambient.y = ambient.intensity * color->y / 255;
	i_ambient.z = ambient.intensity * color->z / 255;
	i_ambient.x = min(1, i_ambient.x);
	i_ambient.y = min(1, i_ambient.y);
	i_ambient.z = min(1, i_ambient.z);
	return (i_ambient);
}

t_vector	ft_calcule_normal_2(t_scene *scene, t_object *object)
{
	t_vector			n;
	t_noraml_variables	nrml;

	if (object->object_type == 'p' || object->object_type == 'q')
	{
		n = object->orientation;
		if (vectorsdot(n, scene->ray->direction) > __DBL_EPSILON__)
			n = vectorscal(n, -1);
	}
	if (object->object_type == 't')
	{
		nrml.edge1 = vectorssub(object->v3[1], object->v3[0]);
		nrml.edge2 = vectorssub(object->v3[2], object->v3[0]);
		nrml.h = vecttorscross(nrml.edge1, nrml.edge2);
		n = normalize(nrml.h);
		if (vectorsdot(n, scene->ray->direction) > __DBL_EPSILON__)
			n = vectorscal(n, -1);
	}
	return (n);
}

t_vector	ft_calcule_normal(t_scene *scene, t_object *object,
			t_vector p, double t)
{
	t_vector			n;
	t_noraml_variables	nrml;

	n = ft_calcule_normal_2(scene, object);
	if (object->object_type == 's')
		n = vectorssub(p, object->origin);
	if (object->object_type == 'c')
	{
		object->orientation = normalize(object->orientation);
		nrml.oc = vectorssub(scene->ray->origin, object->origin);
		nrml.m = vectorsdot(scene->ray->direction, object->orientation) * t
			+ vectorsdot(nrml.oc, object->orientation);
		//    N = nrm( P-C-V*m )
		nrml.normal = vectorssub(p, object->origin);
		nrml.line_point = vectorscal(object->orientation, nrml.m);
		n = vectorssub(nrml.normal, nrml.line_point);
	}
	n = normalize(n);
	return (n);
}

double		ft_hit_objects(t_object *temps, t_ray p_ray)
{
	double	closet_object1_t;

	if (temps->object_type == 'c')
		closet_object1_t = hit_cylinder(p_ray, temps->object);
	if (temps->object_type == 's')
		closet_object1_t = hit_sphere(p_ray, temps->object);
	else if (temps->object_type == 'p')
		closet_object1_t = hit_plane(p_ray, temps->object);
	else if (temps->object_type == 't')
		closet_object1_t = hit_triangle(p_ray, temps->object);
	else if (temps->object_type == 'q')
		closet_object1_t = hit_square(p_ray, temps->object);
	return (closet_object1_t);
}

double		ft_get_first_intersection(t_object *temps, t_ray p_ray,
			t_object *closet_object)
{
	double		closet_object1_t;
	double		closet_object_t;
	t_object	*first_intersection_object;

	closet_object1_t = 0;
	closet_object_t = 1000000000000;
	while (temps != NULL)
	{
		closet_object1_t = ft_hit_objects(temps, p_ray);
		if (closet_object1_t > 0)
			if (closet_object1_t < closet_object_t)
			{
				first_intersection_object = temps;
				closet_object_t = closet_object1_t;
			}
		temps = temps->next;
	}
	// for doesnt intersect with same object with calcule it shadaw
	if (closet_object == first_intersection_object)
		return (10000000000000);
	return (closet_object_t);
}
