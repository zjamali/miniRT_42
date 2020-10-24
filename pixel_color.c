/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:09:11 by zjamali           #+#    #+#             */
/*   Updated: 2020/10/23 20:42:31 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
double rgbconvert(int ir, int ig, int ib)
{
	    return (ir * 65536 + ig * 256+ ib);
}

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
	//ray1.origin = vectorscal(&ray.origin,1);
	ray1.origin.x = ray.origin.x * 100;
	ray1.origin.y = ray.origin.y * 100;
	ray1.origin.z = ray.origin.z * 100; /// cam 1
	ray1.direction = vectorsSub(&ray.origin,&ray1.origin);
	ray1.direction = normalize(&ray1.direction);
	t_ray ray2;
	///ray2.origin = vectorscal(&ray.origin,1);
	ray2.origin.x = ray.origin.x * -100;
	ray2.origin.y = ray.origin.y * -100;
	ray2.origin.z = ray.origin.z * -100; /// cam 2
	ray2.direction = vectorsSub(&ray.origin,&ray2.origin);
	ray2.direction = normalize(&ray2.direction);


	double closet_object1_t = 0;
	double closet_object_t = 000000000000;

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
		double t1 = 100000000;
		double t2 = 100000000;
		while (temp != NULL)
		{
			
			if (temp->object_type == 's')
				closet_object1_t = hit_sphere(ray1,temp->object);
			else if (temp->object_type == 'p')
				closet_object1_t = hit_plane(ray1,temp->object);
			else if (temp->object_type == 't')
				closet_object1_t = hit_triangle(ray1,temp->object);
			else if (temp->object_type == 'q')
				closet_object1_t = hit_square(ray1,temp->object);
			else if (temp->object_type == 'c')
				closet_object1_t = hit_cylinder(ray1,temp->object);
			else if (temp->object_type == 'd')
				closet_object1_t = hit_disk(ray1,temp->object);
			
			if (closet_object1_t < t1)
			{
				t1 = closet_object1_t;
				closet_object = temp;
			}
			temp = temp->next;
		}

		closet_object1_t = t1;
		if (closet_object1_t <= 0)
			return 0;
		

		//////////// p2
		while (temp1 != NULL)
		{
			if (temp1->object_type == 's')
				closet_object_t = hit_sphere(ray1,temp1->object);
			else if (temp1->object_type == 'p')
				closet_object_t = hit_plane(ray1,temp1->object);
			else if (temp1->object_type == 't')
				closet_object_t = hit_triangle(ray1,temp1->object);
			else if (temp1->object_type == 'q')
				closet_object_t = hit_square(ray1,temp1->object);
			else if (temp1->object_type == 'c')
				closet_object_t = hit_cylinder(ray1,temp1->object);
			else if (temp1->object_type == 'd')
				closet_object_t = hit_disk(ray1,temp1->object);

			if (closet_object_t < t2)
			{
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

			//if (p1.x == ray.origin.x && p1.y == ray.origin.y &&
			// 	p2.x == ray.origin.x && p2.y == ray.origin.y)
			//{
				t_vector o;
				o.x = fabs(p1.x + p2.x)/2;
				o.y = fabs(p1.y + p2.y)/2;
				o.z = fabs(p1.z + p2.z) / 2;
				
				t_vector o_p1 = vectorsSub(&p1,&o);
				t_vector o_c = vectorsSub(&ray.origin,&o);
				double r = fabs(o.x);
				double r1 = fabs(o.y);
				double r2 = fabs(o.z);
				
				//write(1,"hello\n",6);

				if(fabs(o_c.x) > r || fabs(o_c.y) > r1 || fabs(o_c.z) > r2)
				{
					//write(1,"hello\n",6);
					return 1;
				}
				else
				{
					return 0;
				}
				
				///r = abs(r) / 2;
			//}
			return 0;
		//}
			
		//temp = temp->next;
		//temp1 = temp1->next;
	}
	return 0;
	
}

int ft_color_of_pixel(t_camera camera,t_ray ray,t_object *object,t_ambient *ambient,t_light *light)
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
	if (check_camera_inside_an_object(camera,object))
		return 0;
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
		if (closet_object1_t > 0)
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
	//if (closet_object_t <= 0)
	//	return 0;
	
	//if (check_camera_inside_an_object(ray,closet_object_t,object))
	//	return 0;
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