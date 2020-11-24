/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:02:08 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/24 13:13:53 by zjamali          ###   ########.fr       */
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
