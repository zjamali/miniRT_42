/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:09:11 by zjamali           #+#    #+#             */
/*   Updated: 2020/10/23 14:46:06 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
double rgbconvert(int ir, int ig, int ib)
{
	    return (ir * 65536 + ig * 256+ ib);
}
int check_camera_inside_an_object(t_ray ray,double t,t_object *object)
{
	t_vector scale_direction_to_p = vectorscal(&ray.direction,t);
	t_vector p = vectorsadd(&ray.origin,&scale_direction_to_p);

	t_vector p_l = vectorsSub(&ray.origin,&p);
	t_ray p_ray;
	p_ray.origin.y = p.y + 0.00001;
	p_ray.origin.x = p.x + 0.00001;
	p_ray.origin.z = p.z + 0.00001;
	p_ray.direction = normalize(&p_l);

	double closet_object1_t = 0;
	double closet_object_t = 1000000000000;

	t_object *temp;
	temp = object;

	while (temp != NULL)
	{
			if (temp->object_type == 'c')
			{
				if (temp->object == temp->object)
					closet_object_t = closet_object_t;
				else
					closet_object1_t = 	hit_cylinder(p_ray,temp->object);
			}
			if (temp->object_type == 's')
				closet_object1_t = hit_sphere(p_ray,temp->object);
			else if (temp->object_type == 'p')
				closet_object1_t = hit_plane(p_ray,temp->object);
			else if(temp->object_type == 't')
				closet_object1_t = hit_triangle(p_ray,temp->object);
			else if(temp->object_type == 'q')
				closet_object1_t = hit_square(p_ray,temp->object);
			//else if(temps->object_type == 'c')
			 	//closet_object1_t = hit_cylinder(p_ray,temps->object);
			else if(temp->object_type == 'd')
				closet_object1_t = hit_disk(p_ray,temp->object);
			//else if (temp->object_type != 'c')
			//	if (temps->object_type == 'c')
			//		closet_object1_t = hit_cylinder(p_ray,temps->object);
			if (closet_object1_t > 0)
				return 1;
			temp = temp->next;
	}
	return 0;
	
}
int ft_color_of_pixel(t_ray ray,t_object *object,t_ambient *ambient,t_light *light)
{
	t_object *closet_object;
	closet_object = NULL;
	double t1;
	double t2;
	t_vector d;
	t_vector colors;
	double amcolor = 0;
	int check = 0;
	t_vector color = {0,0,0};
	double closet_object_t = MAXFLOAT;
	double closet_object1_t = 0;
	t_vector i_specular = {0,0,0};
	t_vector i_diffuse =  {0,0,0};
	t_vector i_ambient =  {0,0,0};
	double shadow = 1;
	t_object *temp ;
	temp = object;
	while (temp != NULL)
	{
		if (temp->object_type == 's')
			closet_object1_t = hit_sphere(ray,temp->object);
		else if (temp->object_type == 'p')
			closet_object1_t = hit_plane(ray,temp->object);
		else if (temp->object_type == 't')
			closet_object1_t = hit_triangle(ray,temp->object);
		else if (temp->object_type == 'q')
			closet_object1_t = hit_square(ray,temp->object);
		else if (temp->object_type == 'c')
			closet_object1_t = hit_cylinder(ray,temp->object);
		else if (temp->object_type == 'd')
			closet_object1_t = hit_disk(ray,temp->object);
		if (closet_object1_t != 0)
		{
			if (closet_object1_t < closet_object_t)
			{
				//if (check_camera_inside_an_object(ray,closet_object1_t,object))
				//	return 0;
				check = 1;
				closet_object_t = closet_object1_t + 0.000001;
				closet_object = temp;
				color = *temp->color;
				//if(temp->object_type == 's' || temp->object_type == 'c')
				//	i_specular = ft_specular(light,ray,closet_object,temp);
				//else
				//{
				//	i_specular.x= 0;
				//	i_specular.y= 0;
				//	i_specular.z= 0; 
				//}
				//i_diffuse = ft_diffuse(light,ray,closet_object,temp,&color);
				//shadow = ft_shadow(temp,object,light,ray,closet_object);
				////printf("%f,%f,%f",temp->color->x,temp->color->y,temp->color->z);
				//i_ambient = ft_ambient(ambient,&color);
				//colors.y =  i_ambient.y * 255 +  shadow *	( i_diffuse.y * 255 +       i_specular.y * 255);
				//colors.x =  i_ambient.x * 255 +  shadow *	( i_diffuse.x * 255 +       i_specular.x * 255);
				//colors.z =  i_ambient.z * 255 +  shadow *	( i_diffuse.z * 255 +       i_specular.z * 255);
			}
		}
		temp = temp->next;
	}
	if (closet_object_t <= 0)
		return 0;
	if (check_camera_inside_an_object(ray,closet_object_t,object))
		return 0;
	if (closet_object != NULL)
	{
		if(closet_object->object_type == 's' || closet_object->object_type == 'c')
			i_specular = ft_specular(light,ray,closet_object_t,closet_object);
		else
		{
			i_specular.x= 0;
			i_specular.y= 0;
			i_specular.z= 0; 
		}
		i_diffuse = ft_diffuse(light,ray,closet_object_t,closet_object,&color);
		if (closet_object->object_type != 'c' || closet_object->object_type != 'd')
			shadow = ft_shadow(closet_object,object,light,ray,closet_object_t);
		////printf("%f,%f,%f",temp->color->x,temp->color->y,temp->color->z);
		i_ambient = ft_ambient(ambient,&color);
		if (shadow < 1)
			i_specular = vectorscal(&i_specular,0);
		colors.y =  i_ambient.y * ambient->color.x  +  shadow *	(i_diffuse.y + i_specular.y );
		colors.x =  i_ambient.x * ambient->color.y  +  shadow *	(i_diffuse.x + i_specular.x );
		colors.z =  i_ambient.z * ambient->color.z  +  shadow *	(i_diffuse.z + i_specular.z );
	}
	
	/************************************/
	if (check == 1){ 
		colors.x = min(255,colors.x);
		colors.y = min(255,colors.y);
		colors.z = min(255,colors.z);
		amcolor = rgbconvert(colors.x,colors.y,colors.z);
	}
	return amcolor;
}