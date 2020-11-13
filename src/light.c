/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:02:08 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/13 14:13:09 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector bzero_vector(t_vector v3)
{
	v3.x = 0;
	v3.y = 0;
	v3.z = 0;
	return v3;
}

t_vector ft_calcule_normal(t_scene *scene,t_object *object,t_vector p,double t)
{
	t_vector n;
	t_noraml_variables nrml;

	if (object->object_type == 's')
		n  = vectorsSub(p,object->origin);
	if (object->object_type == 'p' || object->object_type == 'q')
	{
		n = object->orientation;
		if (vectorsDot(n,scene->ray->direction) > __DBL_EPSILON__) ///
			n = vectorscal(n,-1);
	}
	if (object->object_type == 't')
	{
		nrml.edge1 = vectorsSub(object->v3[1],object->v3[0]); // 1 0 
		nrml.edge2 = vectorsSub(object->v3[2],object->v3[0]); // 2 0
		nrml.h = vecttorscross(nrml.edge1,nrml.edge2);
		n = normalize(nrml.h);
		if (vectorsDot(n,scene->ray->direction) > __DBL_EPSILON__) ///
			n = vectorscal(n,-1);
	}
	if (object->object_type == 'c')
	{
		object->orientation = normalize(object->orientation);
		nrml.oc =  vectorsSub(scene->ray->origin,object->origin);
		nrml.m = vectorsDot(scene->ray->direction,object->orientation) * t 
					+ vectorsDot(nrml.oc,object->orientation);
		//    N = nrm( P-C-V*m )
		nrml.normal = vectorsSub(p,object->origin);
		nrml.line_point = vectorscal(object->orientation,nrml.m);
		n = vectorsSub(nrml.normal,nrml.line_point);
	}
	n = normalize(n);
	return n;
}
double ft_get_first_intersection(t_object *temps,t_ray p_ray,t_object *closet_object)
{
	double closet_object1_t = 0;
	double closet_object_t = 1000000000000;
	t_object *first_intersection_object;
	while (temps != NULL)
		{
			if (temps->object_type == 'c')
					closet_object1_t = 	hit_cylinder(p_ray,temps->object);
			if (temps->object_type == 's')
				closet_object1_t = hit_sphere(p_ray,temps->object);
			else if (temps->object_type == 'p')
				closet_object1_t = hit_plane(p_ray,temps->object);
			else if(temps->object_type == 't')
				closet_object1_t = hit_triangle(p_ray,temps->object);
			else if(temps->object_type == 'q')
				closet_object1_t = hit_square(p_ray,temps->object);
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
			return (1000000000000);
		return closet_object_t;
}
double  ft_shadow(t_scene *scene,double t,t_object *closet_object)
{
	t_shadow_variables shadow;
	shadow.scale_direction_to_p = vectorscal(scene->ray->direction,t);
	shadow.p = vectorsadd(scene->ray->origin,shadow.scale_direction_to_p);
	shadow.dark = 0;
	t_light *light;
	light = scene->light;
	double shadaw = 0;
	while (light != NULL)
	{
		shadow.light_to_p = vectorsSub(shadow.p,light->origin);
		shadow.light_ray.origin = light->origin;
		shadow.light_ray.direction = normalize(shadow.light_to_p);
		shadow.temps = scene->objects;
		shadow.closet_object_t = ft_get_first_intersection(shadow.temps,shadow.light_ray,closet_object);
		shadow.light_to_c = vectorscal(shadow.light_ray.direction,shadow.closet_object_t);
		shadow.light_to_c = vectorsadd(shadow.light_to_c,shadow.light_ray.origin);
		shadow.light_to_c = vectorsSub(shadow.light_to_c,shadow.light_ray.origin);
		shadow.light_to_c_lenght = lenght(shadow.light_to_c);
		shadow.light_to_p_lenght = lenght(shadow.light_to_p);
		if (shadow.light_to_p_lenght > shadow.light_to_c_lenght)
		{
			shadaw = shadaw + 0.4;
			shadow.dark = 1;
		}
		light = light->next;
	}
	if (shadow.dark == 1)
	{
		if (1 - shadaw < 0)
			return 0;
		return (1 - shadaw);
	}
	return 1;
}

t_vector ft_specular(t_scene *scene,double t,t_object *object)
{
	t_phong_variables spr;
	t_light *light;

	spr.scale_direction_to_p = vectorscal(scene->ray->direction,t);
	spr.p = vectorsadd(scene->ray->origin,spr.scale_direction_to_p);
	//spr.p = normalize(spr.p);
	spr.from_camera_to_p = vectorscal(scene->ray->direction,-1);
	spr.from_camera_to_p = normalize(spr.from_camera_to_p);
	spr.specular_shiness = 0;
	if(object->object_type == 's')
		spr.specular_shiness = 256;
	else if (object->object_type == 'c')
		spr.specular_shiness = 50;
	spr.n = ft_calcule_normal(scene,object,spr.p,t);

	spr.color = bzero_vector(spr.color);
	light = scene->light;
	while (light != NULL)
	{
		spr.l_p = vectorsSub(spr.p,light->origin);
		spr.l_p = normalize(spr.l_p);
		spr.dot = vectorsDot(spr.l_p,spr.n);
		spr.r = vectorscal(spr.n,spr.dot * 2);
		spr.reflection = vectorsSub(spr.r,spr.l_p);
		spr.reflection = normalize(spr.reflection);
		spr.dot = vectorsDot(spr.from_camera_to_p,spr.reflection);
		spr.dot =  min (spr.dot,0.0);
		spr.i_specular =  1 * pow(spr.dot,spr.specular_shiness);
		spr.color1 = vectorscal(light->color,spr.i_specular);
		spr.color = vectorsadd(spr.color,spr.color1);
		light = light->next;
	}
	return spr.color;
}

t_vector ft_diffuse(t_scene *scene,double t,t_object *object)
{
	t_phong_variables dfs;

	dfs.scale_direction_to_p = vectorscal(scene->ray->direction,t);
	dfs.p = vectorsadd(scene->ray->origin,dfs.scale_direction_to_p);
	dfs.n = ft_calcule_normal(scene,object,dfs.p,t);
	dfs.color = bzero_vector(dfs.color);
	t_light *light;
	light = scene->light;
	while (light != NULL)
	{
		dfs.l_p = vectorsSub(light->origin,dfs.p);
		dfs.l_p = normalize(dfs.l_p);
		dfs.i_diffuse = vectorsDot(dfs.l_p,dfs.n);
		dfs.i_diffuse = dfs.i_diffuse;
		dfs.i_diffuse = max(0,dfs.i_diffuse);
		dfs.color1.x  = object->color->x /255  * light->color.x  * light->intensity * dfs.i_diffuse;
		dfs.color1.y  = object->color->y /255  * light->color.y  * light->intensity * dfs.i_diffuse;
		dfs.color1.z  = object->color->z /255  * light->color.z  * light->intensity * dfs.i_diffuse;
		light = light->next;
		dfs.color = vectorsadd(dfs.color,dfs.color1);
	}
	return dfs.color;
}
t_vector ft_ambient(t_ambient ambient,t_vector *color)
{
	t_vector i_ambient = {ambient.intensity * color->x /255,
	ambient.intensity * color->y /255 , ambient.intensity * color->z /255};
	i_ambient.x = min(1, i_ambient.x);
	i_ambient.y = min(1, i_ambient.y);
	i_ambient.z = min(1, i_ambient.z);
	return i_ambient;
}