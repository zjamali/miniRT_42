/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:09:11 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/18 14:30:33 by zjamali          ###   ########.fr       */
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
	if (pxl.shadow > (1 - scene->light_number * 0.4) && pxl.shadow != 0)
	{
		//pxl.i_specular = vectorscal(pxl.i_specular, 0);
		//pxl.i_diffuse = vectorscal(pxl.i_diffuse, 0);
		pxl.i_diffuse = ft_diffuse(scene, closet_object_t, closet_object);
		if (closet_object->object_type == 's' || closet_object->object_type == 'c')
		pxl.i_specular = ft_specular(scene, closet_object_t, closet_object);
	}
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
		pxl.colors = ft_calculate_pixel_its_color(scene,
							pxl.closet_object_t, pxl.closet_object);
		pxl.pixel_color = rgbconvert(pxl.colors.x, pxl.colors.y, pxl.colors.z);
	}
	return (pxl.pixel_color);
}
