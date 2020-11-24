/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:02:08 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/24 16:21:26 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_real_check_shadaw(t_vector light_to_c,
t_vector ray_direction)
{
	double dot;

	dot = vectorsdot(light_to_c, ray_direction);
	if (dot > 0)
		return (1);
	else
		return (0);
}

double		ft_calcule_shadaw(t_scene *scene, t_object *closet_object,
		t_light *light, t_shadow_variables *shadow)
{
	shadow->light_to_p = vectorssub(shadow->p, light->origin);
	shadow->light_ray.origin = light->origin;
	shadow->light_ray.direction = normalize(shadow->light_to_p);
	shadow->temps = scene->objects;
	shadow->closet_object_t = ft_get_first_intersection(shadow->temps,
			shadow->light_ray, closet_object);
	shadow->light_to_c = vectorscal(shadow->light_ray.direction,
			shadow->closet_object_t);
	shadow->light_to_c = vectorsadd(shadow->light_to_c,
			shadow->light_ray.origin);
	shadow->light_to_c = vectorssub(shadow->light_to_c,
			shadow->light_ray.origin);
	shadow->light_to_c_lenght = lenght(shadow->light_to_c);
	shadow->light_to_p_lenght = lenght(shadow->light_to_p);
	if (shadow->light_to_p_lenght > shadow->light_to_c_lenght)
	{
		if (ft_real_check_shadaw(shadow->light_to_c,
			scene->ray->direction))
		{
			shadow->shadaw = shadow->shadaw + 0.45;
		}
		shadow->dark = 1;
	}
	return (shadow->shadaw);
}

double		ft_shadow(t_scene *scene, double t, t_object *closet_object)
{
	t_shadow_variables	shadow;
	t_light				*light;

	shadow.scale_direction_to_p = vectorscal(scene->ray->direction, t);
	shadow.p = vectorsadd(scene->ray->origin, shadow.scale_direction_to_p);
	shadow.dark = 0;
	light = scene->light;
	shadow.shadaw = 0;
	while (light != NULL)
	{
		shadow.shadaw = ft_calcule_shadaw(scene, closet_object, light, &shadow);
		light = light->next;
	}
	if (shadow.dark == 1)
	{
		if (1 - shadow.shadaw < 0)
			return (0);
		return (1 - shadow.shadaw);
	}
	return (1);
}
