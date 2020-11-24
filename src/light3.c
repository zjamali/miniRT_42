/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:19:22 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/24 17:54:22 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	ft_calcule_specular(t_light *light, t_phong_variables *spr)
{
	spr->l_p = vectorssub(spr->p, light->origin);
	spr->l_p = normalize(spr->l_p);
	spr->dot = vectorsdot(spr->l_p, spr->n);
	spr->r = vectorscal(spr->n, spr->dot * 2);
	spr->reflection = vectorssub(spr->r, spr->l_p);
	spr->reflection = normalize(spr->reflection);
	spr->dot = vectorsdot(spr->from_camera_to_p, spr->reflection);
	spr->dot = min(spr->dot, 0.0);
	spr->i_specular = spr->ks * pow(spr->dot, spr->specular_shiness);
	spr->color1 = vectorscal(light->color, spr->i_specular);
	return (spr->color1);
}

void		ft_object_shiness(t_phong_variables *spr, t_object *object)
{
	if (object->object_type == 's')
	{
		spr->ks = 0.5;
		spr->specular_shiness = 50;
	}
	else if (object->object_type == 'c')
	{
		spr->ks = 0.2;
		spr->specular_shiness = 2;
	}
	else if (object->object_type == 'p')
	{
		spr->ks = 0.2;
		spr->specular_shiness = 1500;
	}
	else if (object->object_type == 't')
	{
		spr->specular_shiness = 10;
		spr->ks = 0.2;
	}
	else if (object->object_type == 'q')
	{
		spr->specular_shiness = 200;
		spr->ks = 0.2;
	}
}

t_vector	ft_specular(t_scene *scene, double t, t_object *object)
{
	t_phong_variables	spr;
	t_light				*light;

	spr.scale_direction_to_p = vectorscal(scene->ray->direction, t);
	spr.p = vectorsadd(scene->ray->origin, spr.scale_direction_to_p);
	spr.from_camera_to_p = vectorscal(scene->ray->direction, -1);
	spr.from_camera_to_p = normalize(spr.from_camera_to_p);
	spr.specular_shiness = 3000;
	spr.ks = 1;
	ft_object_shiness(&spr, object);
	spr.n = ft_calcule_normal(scene, object, spr.p, t);
	spr.color = bzero_vector();
	light = scene->light;
	while (light != NULL)
	{
		spr.color1 = ft_calcule_specular(light, &spr);
		spr.color = vectorsadd(spr.color, spr.color1);
		light = light->next;
	}
	return (spr.color);
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
	if (closet_object == first_intersection_object)
	{
		return (closet_object_t + 100);
	}
	return (closet_object_t);
}
