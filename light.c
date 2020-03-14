/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:02:08 by zjamali           #+#    #+#             */
/*   Updated: 2020/03/14 17:23:59 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
double  ft_shadow(t_object *temp,t_object *object,t_light *light,t_ray ray,double t)
{
	t_vector scale_direction_to_p = vectorscal(&ray.direction,t);
	t_vector p = vectorsadd(&ray.origin,&scale_direction_to_p);
	t_vector l_p = vectorsSub(&light->origin,&p);
	l_p = normalize(&l_p);
	t_ray rays;
	int check = 0;
	double closet_object1 = 0;
	double closet_object = MAXFLOAT;
	rays.direction = l_p;
	rays.origin = p;
	t_object *temps ;
	temps = object;
	while (temps != NULL)
	{
		if (temps->object_type == 's')
			closet_object1 = hit_sphere(rays,temps->object);
		else if (temps->object_type == 'p')
			closet_object1 = hit_plane(rays,temps->object);
		if (closet_object1 > 0)
		{
			if (closet_object1 < closet_object)
				{
					check = 1;
					closet_object = closet_object1;
				}
		}
		temps = temps->next;
	}
	if (check == 1)
	{
		return 0;
	}
	 return 1;
}
t_vector ft_specular(t_light *light,t_ray ray,double t,t_object *object)
{
	t_vector scale_direction_to_p = vectorscal(&ray.direction,t);
	t_vector p = vectorsadd(&ray.origin,&scale_direction_to_p);
	t_vector n = vectorsSub(&p,&object->origin);
	n = normalize(&n);
	t_vector from_camera_to_p = vectorscal(&p,-1);
	from_camera_to_p = normalize(&from_camera_to_p);
 	t_vector l_p = vectorsSub(&p,&light->origin);
	l_p = normalize(&l_p);
	double dot = vectorsDot(&l_p,&n);
	t_vector r = vectorscal(&n,dot * 2);
	t_vector reflection = vectorsSub(&r,&l_p);
	reflection = normalize(&reflection);
	dot = vectorsDot(&from_camera_to_p,&reflection);
	dot =  min (dot,0.0);
	double i_specular = pow(dot,232);
	t_vector color = {light->color.x /255 * i_specular  * light->intensity,
	  i_specular  * light->color.y /255 * light->intensity,
	  light->color.z  * i_specular /255 * light->intensity};
	return color;
}
t_vector ft_diffuse(t_light *light,t_ray ray,double t,t_object *object,t_vector *colors)
{
	t_vector scale_direction_to_P = vectorscal(&ray.direction,t);
	t_vector p = vectorsadd(&ray.origin,&scale_direction_to_P);
	t_vector n = vectorsSub(&p,&object->origin);
	n = normalize(&n);
	if (object->object_type == 'p')
		n = object->orientation;
	t_vector l_p;
	l_p = vectorsSub(&light->origin,&p);
	l_p = normalize(&l_p);
	double i_diffuse = vectorsDot(&l_p,&n);
	i_diffuse = max(0,i_diffuse);
	t_vector color = { colors->x / 255 *light->color.x /255 * light->intensity * i_diffuse ,
	colors->y  /255* light->intensity  * i_diffuse  * light->color.y /255,colors->z /255 * light->color.z /225 * light->intensity * i_diffuse};
	return color;
}
t_vector ft_ambient(t_ambient *ambient,t_vector *color)
{
	t_vector i_ambient = {ambient->intensity * color->x /255,
	ambient->intensity * color->y /255 , ambient->intensity * color->z /255};
	i_ambient.x = min(1, i_ambient.x);
	i_ambient.y = min(1, i_ambient.y);
	i_ambient.z = min(1, i_ambient.z);
	return i_ambient;
}