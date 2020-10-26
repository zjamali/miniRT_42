/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:02:08 by zjamali           #+#    #+#             */
/*   Updated: 2020/10/26 14:43:05 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector ft_calcule_normal(t_scene *scene,t_object *object,t_vector p,double t)
{
	t_vector n;
	double m;
	if (object->object_type == 's')
		n  = vectorsSub(&p,&object->origin);
	if (object->object_type == 'p')
		n = object->orientation;
	if (object->object_type == 'q')
		n = object->orientation;
	if (object->object_type == 't')
	{
		t_vector edge1 = vectorsSub(&object->v3[1],&object->v3[0]); // 1 0 
		t_vector edge2 = vectorsSub(&object->v3[2],&object->v3[0]); // 2 0
		t_vector h = vecttorscross(&edge1,&edge2);
		n = normalize(&h);
	}
	if (object->object_type == 'c')
	{
		object->orientation = normalize(&object->orientation);
		t_vector oc =  vectorsSub(&scene->ray->origin,&object->origin);
		m = vectorsDot(&scene->ray->direction,&object->orientation) * t + vectorsDot(&oc,&object->orientation);
		//    N = nrm( P-C-V*m )
		t_vector normal = vectorsSub(&p,&object->origin);
		t_vector line_point = vectorscal(&object->orientation,m);
		n = vectorsSub(&normal,&line_point);
	}
	if (object->object_type == 'd')
		n = object->orientation;
	n = normalize(&n);
	return n;
}

double  ft_shadow(t_scene *scene,t_object *object,double t)
{
	t_vector scale_direction_to_p = vectorscal(&scene->ray->direction,t);
	t_vector p = vectorsadd(&scene->ray->origin,&scale_direction_to_p);
	int dark = 0;
	double shadaws = 0;
	t_vector color;
	color.x = 0;
	color.y = 0;
	color.z = 0;
	t_light *light;
	light = scene->light;
	while (light != NULL)
	{
		t_vector p_l = vectorsSub(&light->origin,&p);
		t_ray p_ray;
		p_ray.origin.y = p.y + 0.00001;
		p_ray.origin.x = p.x + 0.00001;
		p_ray.origin.z = p.z + 0.00001;
		p_ray.direction = normalize(&p_l);

		double closet_object1_t = 0;
		double closet_object_t = 1000000000000;
		t_object *temps;
		temps = scene->objects;
		while (temps != NULL)
		{
			if (temps->object_type == 'c')
			{
				if (object->object == temps->object)
					closet_object_t = closet_object_t;
				else
					closet_object1_t = 	hit_cylinder(p_ray,temps->object);
			}
			if (temps->object_type == 's')
				closet_object1_t = hit_sphere(p_ray,temps->object);
			else if (temps->object_type == 'p')
				closet_object1_t = hit_plane(p_ray,temps->object);
			else if(temps->object_type == 't')
				closet_object1_t = hit_triangle(p_ray,temps->object);
			else if(temps->object_type == 'q')
				closet_object1_t = hit_square(p_ray,temps->object);
			else if(temps->object_type == 'd')
				closet_object1_t = hit_disk(p_ray,temps->object);
			if (closet_object1_t > 0)
			{
				if (closet_object1_t < closet_object_t)
					{
						closet_object1_t = closet_object1_t; //  ////// for noises in sceane
						closet_object_t = closet_object1_t; 				
					}
			}
			temps = temps->next;
		}
		
		t_vector scale_direction_to_C = vectorscal(&p_ray.direction,closet_object_t);
		t_vector C = vectorsadd(&p_ray.origin,&scale_direction_to_C);
		t_vector p_C = vectorsSub(&C,&p);
		
		double p_length = lenght(&p_l);
		double c_length = lenght(&p_C);
		if (p_length > c_length && dark <= 1)
			dark = 1;
		else
			dark = 2;
		light = light->next;
	}
	if (dark == 1)
		return 0.2;
	 return 1;
}

t_vector ft_specular(t_scene *scene,double t,t_object *object)
{
	t_vector n;

	t_vector scale_direction_to_p = vectorscal(&scene->ray->direction,t);
	t_vector p = vectorsadd(&scene->ray->origin,&scale_direction_to_p);
	t_vector from_camera_to_p = vectorscal(&p,-1);
	from_camera_to_p = normalize(&from_camera_to_p);
	int specular = 0; ///// 232
	if (object->object_type == 's' || object->object_type == 'c')
	{
		if(object->object_type == 's')
			specular = 256;
		else if (object->object_type == 'c')
			specular = 2;
		n = ft_calcule_normal(scene,object,p,t);
	}
	t_vector color;
	color.x = 0;
	color.y = 0;
	color.z = 0;

	t_light *light;
	light = scene->light;
	while (light != NULL)
	{
		t_vector l_p = vectorsSub(&p,&light->origin);
		l_p = normalize(&l_p);
		double dot = vectorsDot(&l_p,&n);
		t_vector r = vectorscal(&n,dot * 2);
		t_vector reflection = vectorsSub(&r,&l_p);
		reflection = normalize(&reflection);
		dot = vectorsDot(&from_camera_to_p,&reflection);
		dot =  min (dot,0.0);
		double i_specular =  1 * pow(dot,specular);
		t_vector color1 = vectorscal(&light->color,i_specular);
		light = light->next;
		color = vectorsadd(&color,&color1);
	}
	return color;
}

t_vector ft_diffuse(t_scene *scene,double t,t_object *object)
{
	double m;
	t_vector color;
	t_vector scale_direction_to_P = vectorscal(&scene->ray->direction,t);
	t_vector p = vectorsadd(&scene->ray->origin,&scale_direction_to_P);
	t_vector n;

	n = ft_calcule_normal(scene,object,p,t);
	color.x = 0;
	color.y = 0;
	color.z = 0;

	t_light *light;
	light = scene->light;
	while (light != NULL)
	{
		t_vector l_p;
		l_p = vectorsSub(&light->origin,&p);
		l_p = normalize(&l_p);
		double i_diffuse = vectorsDot(&l_p,&n);
		i_diffuse = i_diffuse;
		i_diffuse = max(0,i_diffuse);
		t_vector color1 = { object->color->x /255  * light->color.x  * light->intensity * i_diffuse ,
		object->color->y  /255  * light->intensity  * i_diffuse  * light->color.y ,object->color->z   /255  * light->color.z  * light->intensity * i_diffuse};
		light = light->next;
		color = vectorsadd(&color,&color1);
	}
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