/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:02:08 by zjamali           #+#    #+#             */
/*   Updated: 2020/10/21 14:30:29 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*double  ft_shadow(t_object *temp,t_object *object,t_light *light,t_ray ray,double t)
{
	t_vector scale_direction_to_p = vectorscal(&ray.direction,t);
	t_vector p = vectorsadd(&ray.origin,&scale_direction_to_p);
	t_vector l_p = vectorsSub(&light->origin,&p);
	t_vector l_pp = l_p;
	l_p = normalize(&l_p);
	t_ray rays;
	int check = 0;
	double closet_object1 = 0.0000001f;
	double closet_object = MAXFLOAT;
	//rays.direction = l_p;

	t_vector direction_of_ray = vectorscal(&ray.direction,-1);
	rays.direction = direction_of_ray;
	ray.direction = normalize(&rays.direction);

	rays.origin = p;
	t_object *temps ;
	temps = object;
	while (temps != NULL)
	{
		if (temps->object_type == 's')
			closet_object1 = hit_sphere(rays,temps->object);
		//else if (temps->object_type == 'p')
			//closet_object1 = hit_plane(rays,temps->object);
		if (closet_object1 > 0.0)
		{
			if (closet_object1 < closet_object)
				{
					check = 1;
					t_vector scale_direction_to_i = vectorscal(&rays.origin,closet_object1);
					//t_vector i = vectorsadd(&rays.origin,&scale_direction_to_i);
					t_vector i_p = vectorsSub(&scale_direction_to_i,&rays.origin);
					t_vector l_pa = vectorsSub(&light->origin,&rays.origin);
					double d,c;
					d = lenght(&i_p);
					c = lenght(&l_pa);
					printf("%f	%f\n",d,c);
					if (d < c)
					{
						//return 0;
						check = 1;
					}
					closet_object = closet_object1;
				}
		}
		temps = temps->next;
	}
	if (check == 1)
	{
		return 0;
	}
	//printf("%f\n",closet_object1);
	 return 1;
}

double  ft_shadow(t_object *temp,t_object *object,t_light *light,t_ray ray,double t)
{
	t_vector scale_direction_to_p = vectorscal(&ray.direction,t);
	t_vector p = vectorsadd(&ray.origin,&scale_direction_to_p);
	t_vector l_p = vectorsSub(&light->origin,&p);
	l_p = normalize(&l_p);
	t_ray raysh;
	int check = 0;
	double closet_object1 = 0;
	double closet_object = MAXFLOAT;
	raysh.direction = l_p;
	raysh.origin = p;
	t_object *temps ;
	temps = object;
	while (temps != NULL)
	{
		if (temps->object_type == 's')
			closet_object1 = hit_sphere(raysh,temps->object);
		//else if (temps->object_type == 'p')
			///closet_object1 = hit_plane(raysh,temps->object);
		if (closet_object1 > 0)
		{
			if (closet_object1 < closet_object)
				{
					t_vector scale_direction_to_i = vectorscal(&raysh.origin,closet_object1);
					//t_vector i = vectorsadd(&rays.origin,&scale_direction_to_i);
					t_vector i_p = vectorsSub(&scale_direction_to_i,&raysh.origin);
					t_vector l_pa = vectorsSub(&light->origin,&raysh.origin);
					double d,c;
					d = lenght(&i_p);
					c = lenght(&l_pa);
					if (d > c)
					{
						printf("%.0f,%.0f,%.0f  %.0f,%.0f,%.0f\n",object->color->x,object->color->y,object->color->z,
						temps->color->x,temps->color->y,temps->color->z);
						check = 1;
						closet_object = closet_object1;
					}
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
*/

double  ft_shadow(t_object *temp,t_object *object,t_light *light,t_ray ray,double t)
{
	t_vector scale_direction_to_p = vectorscal(&ray.direction,t);
	t_vector p = vectorsadd(&ray.origin,&scale_direction_to_p);
	int dark = 0;
	int if_light = 0;
	double shadaws = 0;
	t_vector color;
	color.x = 0;
	color.y = 0;
	color.z = 0;
	while (light != NULL)
	{
		t_vector p_l = vectorsSub(&light->origin,&p);
		t_ray p_ray;
		p_ray.origin.x = p.x + 0.001;
		p_ray.origin.y = p.y + 0.001;
		p_ray.origin.z = p.z + 0.001;
		p_ray.direction = normalize(&p_l);

		double closet_object1_t = 0;
		double closet_object_t = 1000000000000;
		t_object *temps;
		temps = object;
		while (temps != NULL)
		{
			if (temps->object_type == 'c')
			{
				if (temp->object == temps->object)
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
			//else if(temps->object_type == 'c')
			 	//closet_object1_t = hit_cylinder(p_ray,temps->object);
			else if(temps->object_type == 'd')
				closet_object1_t = hit_disk(p_ray,temps->object);
			//else if (temp->object_type != 'c')
			//	if (temps->object_type == 'c')
			//		closet_object1_t = hit_cylinder(p_ray,temps->object);
			if (closet_object1_t > 0)
			{
				if (closet_object1_t < closet_object_t)
					{
						///printf("%f\n",closet_object1_t);
						closet_object1_t = closet_object1_t; //  ////// for noises in sceane
						closet_object_t = closet_object1_t; 
						//t_vector scale_direction_to_i = vectorscal(&light_ray.direction,closet_object1_t);
						////t_vector newray = {light_ray.origin.x - 0.001,light_ray.origin.y - 0.001,light_ray.origin.z - 0.001,};
						//t_vector i = vectorsadd(&light_ray.origin,&scale_direction_to_i);
						////printf("%f,%f,%f  %f,%f,%f  %f,%f,%f\n",i.x,i.y,i.z,
						//	//p.x,p.y,p.z,l_p.x,l_p.y,l_p.z);
						//t_vector i_l = vectorsSub(&light_ray.origin,&i);
						//t_vector l_pa = vectorsSub(&light_ray.origin,&p);
						//double d,c;
						//d = lenght(&i_l);
						//c = lenght(&l_pa);
						////double k = vectorsDot(&i_l,&l_pa);
						////printf("%f\n",k);
						//if (d < c && dark <= 1)
						//{
						//	 dark = 1;
						//	closet_object_t = closet_object1_t;
						//}
						//else
						//{
						//	dark = 2;
						//}						
					}
			}
			temps = temps->next;
		}
		
		t_vector scale_direction_to_C = vectorscal(&p_ray.direction,closet_object_t);
		t_vector C = vectorsadd(&p_ray.origin,&scale_direction_to_C);
		t_vector p_C = vectorsSub(&C,&p);
		
		double p_length = lenght(&p_l);
		///p_length = p_length  + 0.1;  ////// for noises in sceane
		double c_length = lenght(&p_C);
		
		///printf("%f|%f\n",p_length,c_length);
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

t_vector ft_specular(t_light *light,t_ray ray,double t,t_object *object)
{
	t_vector n;
	t_vector scale_direction_to_p = vectorscal(&ray.direction,t);
	t_vector p = vectorsadd(&ray.origin,&scale_direction_to_p);
/*	if (object->object_type == 't')
	{
		t_vector edge1 = vectorsSub(&object->v3[1],&object->v3[0]); // 1 0 
		t_vector edge2 = vectorsSub(&object->v3[2],&object->v3[0]); // 2 0
		t_vector h = vecttorscross(&edge1,&edge2);
		n = normalize(&h);
	}
	if (object->object_type == 'q')
		n = object->orientation;
	n = normalize(&n);
	*/
	t_vector from_camera_to_p = vectorscal(&p,-1);
	from_camera_to_p = normalize(&from_camera_to_p);
/*
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
*/
	int specular = 0; ///// 232
	double m;
	if (object->object_type == 's')
	{
		n = vectorsSub(&p,&object->origin);
		n = normalize(&n);
		specular = 256;
	}
	else if (object->object_type == 'c')
	{
		specular = 2;
		object->orientation = normalize(&object->orientation);
		t_vector oc =  vectorsSub(&ray.origin,&object->origin);
		m = vectorsDot(&ray.direction,&object->orientation) * t + vectorsDot(&oc,&object->orientation);
		//    N = nrm( P-C-V*m )
		t_vector normal = vectorsSub(&p,&object->origin);
		t_vector line_point = vectorscal(&object->orientation,m);
		n = vectorsSub(&normal,&line_point);
		n = normalize(&n);
	}

	t_vector color;
	color.x = 0;
	color.y = 0;
	color.z = 0;
	while (light != NULL)
	{
		t_vector l_p = vectorsSub(&p,&light->origin);
		l_p = normalize(&l_p);
		double dot = vectorsDot(&l_p,&n);
		t_vector r = vectorscal(&n,dot * 2);
		t_vector reflection = vectorsSub(&r,&l_p);
		reflection = normalize(&reflection);
		////////////
		dot = vectorsDot(&from_camera_to_p,&reflection);
		/////////
		dot =  min (dot,0.0);
		double i_specular =  1 * pow(dot,specular);
		//t_vector color1 = {light->color.x /255 * i_specular  * light->intensity,
		//  i_specular  * light->color.y /255 * light->intensity,
		//  light->color.z  * i_specular /255 * light->intensity};
		//
		// i_specular = vectorscal(&i_specular,0.5);
		t_vector color1 = vectorscal(&light->color,i_specular);
		light = light->next;
		color = vectorsadd(&color,&color1);
		//color = color1;
	}
	return color;
}
t_vector ft_diffuse(t_light *light,t_ray ray,double t,t_object *object,t_vector *colors)
{
	double m;
	double static new;
	t_vector scale_direction_to_P = vectorscal(&ray.direction,t);
	t_vector p = vectorsadd(&ray.origin,&scale_direction_to_P);
	t_vector n = vectorsSub(&p,&object->origin);
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
		t_vector oc =  vectorsSub(&ray.origin,&object->origin);
		m = vectorsDot(&ray.direction,&object->orientation) * t + vectorsDot(&oc,&object->orientation);
		//    N = nrm( P-C-V*m )
		t_vector normal = vectorsSub(&p,&object->origin);
		t_vector line_point = vectorscal(&object->orientation,m);
		n = vectorsSub(&normal,&line_point);
	}
	if (object->object_type == 'd')
		n = object->orientation;
	n = normalize(&n);

	t_vector color;
	color.x = 0;
	color.y = 0;
	color.z = 0;
	while (light != NULL)
	{
		t_vector l_p;
		l_p = vectorsSub(&light->origin,&p);
		l_p = normalize(&l_p);
		double i_diffuse = vectorsDot(&l_p,&n);
		i_diffuse = i_diffuse;
		i_diffuse = max(0,i_diffuse);
		t_vector color1 = { colors->x /255  * light->color.x  * light->intensity * i_diffuse ,
		colors->y  /255  * light->intensity  * i_diffuse  * light->color.y ,colors->z   /255  * light->color.z  * light->intensity * i_diffuse};
		//t_vector color1 = vectorscal(colors,i_diffuse);
		light = light->next;
		color = vectorsadd(&color,&color1);
		//color = color1;
	}
	return color;
}
t_vector ft_ambient(t_ambient *ambient,t_vector *color)
{
	t_vector i_ambient = {ambient->intensity * color->x /255,
	ambient->intensity * color->y /255 , ambient->intensity * color->z /255};
	//printf("%f,%f,%f",color->x,color->y,color->z);
	//printf("%f,%f,%f",ambient->color.x,ambient->color.y,ambient->color.z);
	
	//t_vector i_ambient = {ambient->intensity * color->x /255 + ambient->color.x/255 * ambient->intensity,
	//ambient->intensity * color->y /255 + ambient->color.y/255 * ambient->intensity, ambient->intensity * color->z /255 + ambient->color.z/255 * ambient->intensity};
	i_ambient.x = min(1, i_ambient.x);
	i_ambient.y = min(1, i_ambient.y);
	i_ambient.z = min(1, i_ambient.z);
	return i_ambient;
}