/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:09:11 by zjamali           #+#    #+#             */
/*   Updated: 2020/10/26 14:21:22 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
double rgbconvert(int ir, int ig, int ib)
{
	    return (ir * 65536 + ig * 256+ ib);
}
/*
int check_camera_inside_an_object(t_camera camera,t_object *object)
{
	//t_vector scale_direction_to_p = vectorscal(&ray.direction,t);
	//t_vector p = vectorsadd(&ray.origin,&scale_direction_to_p);

	//t_vector p_l = vectorsSub(&ray.origin,&p);
	//t_vector p_l = vectorscal(&ray.direction,-1);
	//t_ray p_ray;
	
	//p_ray.origin.y = p.y - 0.000001;
	//p_ray.origin.x = p.x - 0.000001;
	//p_ray.origin.z = p.z - 0.000001;
	//if (ray.direction.x >= 0 && p.x > 0)
	//	p_ray.origin.x = p.x - 0.000001;
	//else
	//	p_ray.origin.x = p.x + 0.000001;
	//if (ray.direction.y >= 0 && p.y > 0)
	//	p_ray.origin.y = p.y - 0.000001;
	//else
	//	p_ray.origin.y = p.y + 0.000001;
	//if (ray.direction.z >= 0 && p.z > 0)
	//	p_ray.origin.z = p.z - 0.000001;
	//else
	//	p_ray.origin.z = p.z + 0.000001;
	///if (p_ray.direction.y < 0)
	///	p_ray.origin.y = p.y - 0.000001;
	///else
	///	p_ray.origin.y = p.y + 0.000001;
	//if (ray.origin.z <= 0)
	//{	
	//	p_ray.origin.x = p.x - 0.000001;
	//	p_ray.origin.y = p.y - 0.000001;
	//	p_ray.origin.z = p.z - 0.000001;
	//}
	//else
	//{
	//	p_ray.origin.x = p.x;// + 0.1;
	//	p_ray.origin.y = p.y;// + 0.1;
	//	p_ray.origin.z = p.z;// + 0.1;
	//}
	//p_ray.direction = normalize(&p_l);

	//write(1,"hello\n",6);


	t_ray ray;
	ray.direction = camera.orientaion;
	ray.origin = camera.lookfrom;
	
	t_ray ray1;
	t_ray ray2;
	ray1.origin = vectorscal(&ray.origin,1000);
	//ray1.origin.x = ray.origin.x * 1000;
	//ray1.origin.y = ray.origin.y * 1000;
	//ray1.origin.z = ray.origin.z * 1000; /// cam 1
	ray1.direction = vectorsSub(&ray.origin,&ray1.origin);
	//ray1.direction = normalize(&ray1.direction);
	ray.direction = vectorscal(&ray.direction,1);
	///ray2.origin = vectorscal(&ray.origin,1);
	//ray2.origin.x = ray.origin.x * 1000;
	//ray2.origin.y = ray.origin.y * 1000;
	//ray2.origin.z = ray.origin.z * 1000; /// cam
	ray2.origin = vectorscal(&ray.origin,1000);
	ray2.origin = vectorscal(&ray2.origin,-1);
	ray2.direction = vectorsSub(&ray.origin,&ray2.origin);
	//ray2.direction = normalize(&ray2.direction);
	///ray2.direction = vectorscal(&ray.direction,-1);
	
	//printf("%f,%f,%f|",ray1.origin.x,ray1.origin.y,ray1.origin.z);
	//printf("%f,%f,%f|",ray2.origin.x,ray2.origin.y,ray2.origin.z);
	//printf("%f,%f,%f\n",ray.origin.x,ray.origin.y,ray.origin.z);

	double closet_object1_t = 100000000;
	double closet_object_t  = 100000000;
	static int i = 0;
	static int j = 0;
	t_object *temp;
	temp = object;
	t_object *temp1;
	temp1 = object;
	t_object *closet_object;
	t_object *closet_object1;
	//while (temp != NULL)
	//{
		//write(1,"hello\n",6);
		///////////////// p1 
	//	write(1,"hello\n",6);
		double t1 = 0;
		double t2 = 0;
		while (temp != NULL)
		{
			
			if (temp->object_type == 's')
				closet_object1_t = hit_sphere(ray1,temp->object);
			//else if (temp->object_type == 'p')
			//	closet_object1_t = hit_plane(ray1,temp->object);
			else if (temp->object_type == 't')
				closet_object1_t = hit_triangle(ray1,temp->object);
			else if (temp->object_type == 'q')
				closet_object1_t = hit_square(ray1,temp->object);
			else if (temp->object_type == 'c')
				closet_object1_t = hit_cylinder(ray1,temp->object);
			else if (temp->object_type == 'd')
				closet_object1_t = hit_disk(ray1,temp->object);
			if (closet_object1_t > 0 && i == 0)
			{
				//write(1,"hello\n",6);
				t1 = closet_object1_t;
				i++;	
			}
			if (closet_object1_t >= t1 && closet_object1_t > 0)
			{
				//write(1,"hello\n",6);
				t1 = closet_object1_t;
				closet_object = temp;
			}
			temp = temp->next;
		}
		closet_object1_t = t1;
		//printf("%f\n",closet_object1_t);
		if (closet_object1_t <= 0)
			return 0;
		

		//////////// p2
		while (temp1 != NULL)
		{
			if (temp1->object_type == 's')
				closet_object_t = hit_sphere(ray1,temp1->object);
			//else if (temp1->object_type == 'p')
			//	closet_object_t = hit_plane(ray1,temp1->object);
			else if (temp1->object_type == 't')
				closet_object_t = hit_triangle(ray1,temp1->object);
			else if (temp1->object_type == 'q')
				closet_object_t = hit_square(ray1,temp1->object);
			else if (temp1->object_type == 'c')
				closet_object_t = hit_cylinder(ray1,temp1->object);
			else if (temp1->object_type == 'd')
				closet_object_t = hit_disk(ray1,temp1->object);
			if (closet_object_t > 0 && j == 0)
			{
				t2 = closet_object_t;
				j++;	
			}
			if (closet_object_t >= t2 && closet_object_t > 0)
			{
				//write(1,"hello1\n",7);
				t2 = closet_object_t;
				closet_object1 = temp1;
			}
			temp1 = temp1->next;
		}

		closet_object_t = t2;
		if (closet_object_t <= 0)
			return 0;
		
		if (closet_object1_t > 0 && closet_object_t > 0 && closet_object == closet_object1)
		{
			//printf("%c|%c\n",temp->object_type,temp1->object_type);
			t_vector scale_direction_to_p1 = vectorscal(&ray1.direction,closet_object1_t);
			t_vector p1 = vectorsadd(&ray1.origin,&scale_direction_to_p1);

			t_vector scale_direction_to_p2 = vectorscal(&ray2.direction,closet_object_t);
			t_vector p2 = vectorsadd(&ray2.origin,&scale_direction_to_p2);

			t_vector o;
			o.x = (p1.x + p2.x) /2;
			o.y = (p1.y + p2.y )/2;
			o.z = (p1.z + p2.z )/2;
			//printf("%f,%f,%f|",p1.x,p1.y,p1.z);
			//printf("%f,%f,%f|",p2.x,p2.y,p2.z);
			//printf("%f,%f,%f\n",o.x,o.y,o.z);
			t_vector p1_p2 = vectorsSub(&p1,&p2);
			
			t_vector o_p1 = vectorsSub(&p1,&o);
			t_vector o_c = vectorsSub(&ray.origin,&o);
			//t_vector u = vectorsSub(&p1,&o);
			double r = fabs(o_p1.x);
			double r1 = fabs(o_p1.y);
			double r2 = fabs(o_p1.z);
			
			
			if(fabs(o_c.x) <= r && fabs(o_c.y) <= r1 && fabs(o_c.z) <= r2)
			{
				///write(1,"hello\n",6);
				return 1;
			}
			//else
			//{
			//	return 0;
			//}	
			return 0;
			
		}
	return 0;
}
*/
double calcule_closet_object_is_t(t_ray *ray,t_object *temp)
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
	else if (temp->object_type == 'd')
		t = hit_disk(*ray,temp->object);
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
	if (closet_object->object_type != 'c' || closet_object->object_type != 'd')
		shadow = ft_shadow(scene, closet_object,closet_object_t);
	i_ambient = ft_ambient(scene->ambient,closet_object->color);
	if (shadow < 1)
		i_specular = vectorscal(&i_specular,0);
	colors.y =  i_ambient.y * scene->ambient->color.x  +  shadow *	(i_diffuse.y + i_specular.y );
	colors.x =  i_ambient.x * scene->ambient->color.y  +  shadow *	(i_diffuse.x + i_specular.x );
	colors.z =  i_ambient.z * scene->ambient->color.z  +  shadow *	(i_diffuse.z + i_specular.z );
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
	double shadow = 1;
	t_object *temp ;
	temp = scene->objects;
	///if (check_camera_inside_an_object(camera,object))
	///	return 0;
	while (temp != NULL)
	{
		closet_object1_t = calcule_closet_object_is_t(scene->ray,temp);
		if (closet_object1_t > 0)
		{
			if (closet_object1_t < closet_object_t)
			{
				closet_object_t = closet_object1_t + 0.000001;
				closet_object = temp;
			}
		}
		temp = temp->next;
	}
	if (closet_object != NULL)
	{
		colors = ft_calculate_pixel_its_color(scene,closet_object_t,closet_object);
		colors.x = min(255,colors.x);
		colors.y = min(255,colors.y);
		colors.z = min(255,colors.z);
		amcolor = rgbconvert(colors.x,colors.y,colors.z);
	}
	return amcolor;
}