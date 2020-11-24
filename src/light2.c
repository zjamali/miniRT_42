/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:34:23 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/24 17:54:08 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	ft_ambient(t_ambient ambient, t_vector color)
{
	t_vector i_ambient;

	i_ambient.x = ambient.intensity * color.x / 255;
	i_ambient.y = ambient.intensity * color.y / 255;
	i_ambient.z = ambient.intensity * color.z / 255;
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
	{
		n = vectorssub(p, object->origin);
	}
	if (object->object_type == 'c')
	{
		object->orientation = normalize(object->orientation);
		nrml.oc = vectorssub(scene->ray->origin, object->origin);
		nrml.m = vectorsdot(scene->ray->direction, object->orientation) * t
			+ vectorsdot(nrml.oc, object->orientation);
		nrml.normal = vectorssub(p, object->origin);
		nrml.line_point = vectorscal(object->orientation, nrml.m);
		n = vectorssub(nrml.normal, nrml.line_point);
	}
	n = normalize(n);
	return (n);
}

t_vector	ft_diffuse(t_scene *scene, double t, t_object *object)
{
	t_phong_variables	dfs;
	t_light				*light;

	dfs.scale_direction_to_p = vectorscal(scene->ray->direction, t);
	dfs.p = vectorsadd(scene->ray->origin, dfs.scale_direction_to_p);
	dfs.n = ft_calcule_normal(scene, object, dfs.p, t);
	dfs.color = bzero_vector();
	light = scene->light;
	while (light != NULL)
	{
		dfs.l_p = vectorssub(light->origin, dfs.p);
		dfs.l_p = normalize(dfs.l_p);
		dfs.i_diffuse = vectorsdot(dfs.l_p, dfs.n);
		dfs.i_diffuse = dfs.i_diffuse;
		dfs.i_diffuse = max(0, dfs.i_diffuse);
		dfs.color1.x = object->color.x / 255 * light->color.x
			* light->intensity * dfs.i_diffuse;
		dfs.color1.y = object->color.y / 255 * light->color.y
			* light->intensity * dfs.i_diffuse;
		dfs.color1.z = object->color.z / 255 * light->color.z
			* light->intensity * dfs.i_diffuse;
		light = light->next;
		dfs.color = vectorsadd(dfs.color, dfs.color1);
	}
	return (dfs.color);
}
