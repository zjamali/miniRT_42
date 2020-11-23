/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dark.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:38:11 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/18 19:39:51 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double					ft_get_intersection(t_object *temps, t_ray p_ray,
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
	{
		return (closet_object_t + 0.05);
		//return (10000000000000);
	}
	return (closet_object_t);
}

t_shadow_variables		ft_calcule_darkness(t_shadow_variables dark)
{
	dark.light_to_c = vectorscal(dark.light_ray.direction,
			dark.closet_object_t);
	dark.light_to_c = vectorsadd(dark.light_to_c,
			dark.light_ray.origin);
	dark.light_to_c = vectorssub(dark.light_to_c,
			dark.light_ray.origin);
	dark.light_to_c_lenght = lenght(dark.light_to_c);
	//dark.light_to_c_lenght = dark.light_to_c_lenght;
	dark.light_to_p_lenght = lenght(dark.light_to_p);
	return (dark);
}

int						ft_chech_pixel_in_dark(t_scene *scene,
		t_object *closet_object, double t)
{
	t_shadow_variables	dark;
	t_light				*light;

	dark.scale_direction_to_p = vectorscal(scene->ray->direction, t);
	dark.p = vectorsadd(scene->ray->origin, dark.scale_direction_to_p);
	dark.dark = 0;
	light = scene->light;
	while (light != NULL)
	{
		dark.light_to_p = vectorssub(dark.p, light->origin);
		dark.light_ray.origin = light->origin;
		dark.light_ray.direction = normalize(dark.light_to_p);
		dark.temps = scene->objects;
		dark.closet_object_t = ft_get_intersection(dark.temps,
				dark.light_ray, closet_object);
		dark = ft_calcule_darkness(dark);
		if (dark.light_to_p_lenght > dark.light_to_c_lenght)
			dark.dark = dark.dark + 1;
		light = light->next;
	}
	if (dark.dark == scene->light_number)
		return (0);
	return (1);
}
