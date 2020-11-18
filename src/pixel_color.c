/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:09:11 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/18 17:43:02 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double			ft_calcule_objects__t(t_ray *ray, t_object *temp)
{
	double t;

	t = 0;
	if (temp->object_type == 's')
		t = hit_sphere(*ray, temp->object);
	else if (temp->object_type == 'p')
		t = hit_plane(*ray, temp->object);
	else if (temp->object_type == 't')
		t = hit_triangle(*ray, temp->object);
	else if (temp->object_type == 'q')
		t = hit_square(*ray, temp->object);
	else if (temp->object_type == 'c')
		t = hit_cylinder(*ray, temp->object);
	return (t);
}

t_pixel_color	ft_init_pixel_color(t_scene *scene)
{
	t_pixel_color pixel_color;

	pixel_color.pixel_color = 0;
	pixel_color.closet_object_t = MAXFLOAT;
	pixel_color.closet_object1_t = 0;
	pixel_color.closet_object = NULL;
	pixel_color.temp = scene->objects;
	pixel_color.shadow = 0;
	pixel_color.colors = bzero_vector();
	pixel_color.i_specular = bzero_vector();
	pixel_color.i_diffuse = bzero_vector();
	pixel_color.i_ambient = bzero_vector();
	return (pixel_color);
}

t_vector		ft_calculate_pixel_its_color(t_scene *scene,
					double closet_object_t, t_object *closet_object)
{
	t_pixel_color pxl;

	pxl = ft_init_pixel_color(scene);
	
	pxl.shadow = ft_shadow(scene, closet_object_t, closet_object);
	pxl.i_ambient = ft_ambient(scene->ambient, closet_object->color);
		if (closet_object->object_type == 's' || closet_object->object_type == 'c')
	pxl.i_specular = ft_specular(scene, closet_object_t, closet_object);
	if (pxl.shadow < 1)
		pxl.i_specular = vectorscal(pxl.i_specular,0);
	pxl.i_diffuse = ft_diffuse(scene, closet_object_t, closet_object);
	pxl.colors.y = pxl.i_ambient.y * scene->ambient.color.x + pxl.shadow *
									(pxl.i_diffuse.y + pxl.i_specular.y);
	pxl.colors.x = pxl.i_ambient.x * scene->ambient.color.y + pxl.shadow *
									(pxl.i_diffuse.x + pxl.i_specular.x);
	pxl.colors.z = pxl.i_ambient.z * scene->ambient.color.z + pxl.shadow *
									(pxl.i_diffuse.z + pxl.i_specular.z);
	pxl.colors.x = min(255, pxl.colors.x);
	pxl.colors.y = min(255, pxl.colors.y);
	pxl.colors.z = min(255, pxl.colors.z);
	return (pxl.colors);
}

double		ft_get_intersection(t_object *temps, t_ray p_ray,
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
	(void)closet_object;
	// for doesnt intersect with same object with calcule it shadaw
	if (closet_object == first_intersection_object)
	{
		return (closet_object_t  + 0.05);
		//return (10000000000000);
	}
	return (closet_object_t);
}



int				ft_chech_pixel_in_dark(t_scene *scene,
						t_object *closet_object , double t)
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
		shadow.light_to_p = vectorssub(shadow.p, light->origin);
		shadow.light_ray.origin = light->origin;
		shadow.light_ray.direction = normalize(shadow.light_to_p);
		shadow.temps = scene->objects;
		shadow.closet_object_t = ft_get_intersection(shadow.temps,
		shadow.light_ray, closet_object);
		shadow.light_to_c = vectorscal(shadow.light_ray.direction,
		shadow.closet_object_t);
		shadow.light_to_c = vectorsadd(shadow.light_to_c,
		shadow.light_ray.origin);
		shadow.light_to_c = vectorssub(shadow.light_to_c,
		shadow.light_ray.origin);
		shadow.light_to_c_lenght = lenght(shadow.light_to_c);
		shadow.light_to_c_lenght = shadow.light_to_c_lenght;
		shadow.light_to_p_lenght = lenght(shadow.light_to_p);
		if (shadow.light_to_p_lenght > shadow.light_to_c_lenght)
		{
			shadow.dark = shadow.dark + 1;
		}
		light = light->next;
	}
	if (shadow.dark == scene->light_number)
		return (0);
	return 1;
}

int				ft_color_of_pixel(t_scene *scene)
{
	t_pixel_color pxl;

	pxl = ft_init_pixel_color(scene);
	while (pxl.temp != NULL)
	{
		pxl.closet_object1_t = ft_calcule_objects__t(scene->ray, pxl.temp);
		if (pxl.closet_object1_t > 0)
		{
			if (pxl.closet_object1_t < pxl.closet_object_t)
			{
				pxl.closet_object_t = pxl.closet_object1_t;
				pxl.closet_object = pxl.temp;
			}
		}
		pxl.temp = pxl.temp->next;
	}
	if (pxl.closet_object != NULL)
	{
		if (ft_chech_pixel_in_dark(scene,pxl.closet_object, pxl.closet_object_t) != 0)
		{
				pxl.colors = ft_calculate_pixel_its_color(scene,
							pxl.closet_object_t, pxl.closet_object);
		}
		else
			pxl.colors = vectorscal(ft_ambient(scene->ambient,pxl.closet_object->color),255);
		pxl.pixel_color = rgbconvert(pxl.colors.x, pxl.colors.y, pxl.colors.z);
	}
	return (pxl.pixel_color);
}
