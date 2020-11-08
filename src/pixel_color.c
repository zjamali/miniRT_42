/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:09:11 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/07 18:30:34 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double rgbconvert(int ir, int ig, int ib)
{
	    return (ir * 65536 + ig * 256+ ib);
}
double ft_calcule_objects__t(t_ray *ray,t_object *temp)
{
	double t;
	t = 0;
	if (temp->object_type == 's')
		t = hit_sphere(*ray,temp->object);
	else if (temp->object_type == 'p')
		t = hit_plane(*ray,temp->object);
	else if (temp->object_type == 't')
		t = hit_triangle(*ray,temp->object);
	else if (temp->object_type == 'q')
		t = hit_square(*ray,temp->object);
	else if (temp->object_type == 'c')
		t = hit_cylinder(*ray,temp->object);
	
	return t;
}

t_vector ft_calculate_pixel_its_color(t_scene *scene,double closet_object_t,t_object *closet_object)
{
	t_vector colors = {0,0,0};
	t_vector i_specular = {0,0,0};
	t_vector i_diffuse =  {0,0,0};
	t_vector i_ambient =  {0,0,0};
	double shadow = 1;

	if(closet_object->object_type == 's' || closet_object->object_type == 'c')
			i_specular = ft_specular(scene,closet_object_t,closet_object);
	i_diffuse = ft_diffuse(scene,closet_object_t,closet_object);
	//if (closet_object->object_type != 'c')
		shadow = ft_shadow(scene,closet_object_t,closet_object);
	i_ambient = ft_ambient(scene->ambient,closet_object->color);
	if (shadow < 1)
		i_specular = vectorscal(i_specular,0);
	colors.y =  i_ambient.y * scene->ambient.color.x  +  shadow *	(i_diffuse.y + i_specular.y );
	colors.x =  i_ambient.x * scene->ambient.color.y  +  shadow *	(i_diffuse.x + i_specular.x );
	colors.z =  i_ambient.z * scene->ambient.color.z  +  shadow *	(i_diffuse.z + i_specular.z );
	colors.x = min(255,colors.x);
	colors.y = min(255,colors.y);
	colors.z = min(255,colors.z);
	return colors;
}

int ft_color_of_pixel(t_scene *scene)
{
	t_object *closet_object;
	closet_object = NULL;
	t_vector colors;
	double amcolor = 0;
	double closet_object_t = MAXFLOAT;
	double closet_object1_t = 0;
	t_object *temp ;
	temp = scene->objects;
	while (temp != NULL)
	{
		closet_object1_t = ft_calcule_objects__t(scene->ray,temp);
		if (closet_object1_t > 0)
		{
			if (closet_object1_t < closet_object_t)
			{
				closet_object_t = closet_object1_t;
				closet_object = temp;
			}
		}
		temp = temp->next;
	}
	if (closet_object != NULL)
	{
		colors = ft_calculate_pixel_its_color(scene,closet_object_t,closet_object);
		amcolor = rgbconvert(colors.x,colors.y,colors.z);
	}
	return amcolor;
}