/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:09:11 by zjamali           #+#    #+#             */
/*   Updated: 2020/03/11 19:44:12 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double rgbconvert(int ir, int ig, int ib)
{
	    return (ir * 65536 + ig * 256+ ib);
}
int ft_color_of_pixel(t_ray ray,t_object *object,t_ambient *ambient,t_light *light)
{
	t_vector colors;
	double amcolor = 0;
	int check = 0;
	t_vector color = {0,0,0};
	double closet_object = MAXFLOAT;
	double closet_object1 = 0;
	t_object *temp;
	t_vector i_specular = {0,0,0};
	t_vector i_diffuse = {0,0,0};
	t_vector i_ambient = {0,0,0};
	while(object != NULL)
	{
		//printf("k %d %f",object->id,ray.origin.x);
		closet_object1 = hit_sphere(ray,object->object);
		if (closet_object1 != 0)
		{
				// printf("(%f,%f,%f)\n",object->color->x,object->color->y,object->color->z);
			if (closet_object1 < closet_object)
				{
					check = 1;
					closet_object = closet_object1;
					color = *object->color;
					i_diffuse = ft_diffuse(light,ray,closet_object,object,&color);
					i_ambient = ft_ambient(ambient,&color);
					i_specular = ft_specular(light,ray,closet_object,object);
					colors.y =  i_ambient.y * 255 +  	 i_diffuse.y * 255 +    0*    i_specular.y * 255;
					colors.x =  i_ambient.x * 255 +    	 i_diffuse.x * 255 +    0*   i_specular.x * 255;
					colors.z =  i_ambient.z * 255 + 	 i_diffuse.z * 255 +    0*    i_specular.z * 255;
				}
		}
		object = object->next;
	}
	/************************************/
	if (check == 1){ // to dont color the other pixels 
//	t_vector i_ambient = ft_ambient(ambient,&color);
//	t_vector i_diffuse = ft_diffuse(light,ray,closet_object,temp,&color);
	//t_vector i_specular = ft_specular(light,ray,closet_object,temp);
	//printf("(%f,%f,%f)\n",i_diffuse.x,i_diffuse.y,i_diffuse.z);
	//t_vector i_specular = ft_specular(light,ray,closet_object,temp);
	/************************************/


	//if (i_diffuse.x > 255)
	//  	i_diffuse.x = 255;
	// if (i_diffuse.y > 255)
	//  	i_diffuse.y = 255;
	// if (i_diffuse.z > 255)
	//  	i_diffuse.z = 255;
	
	
	// colors.x =  i_ambient.x * 255 +    	 i_diffuse.x +       0*i_specular.x * 255;
	// colors.y =  i_ambient.y * 255 +  	 i_diffuse.y +        0*i_specular.y * 255;
	// colors.z =  i_ambient.z * 255 + 	 i_diffuse.z +        0*i_specular.z * 255;
	//printf("|x ===> %f|\t|y ==> %f|\t| z ==> %f|\t",i_diffuse.x,i_diffuse.y,i_diffuse.z);
	colors.x = min(255,colors.x);
	colors.y = min(255,colors.y);
	colors.z = min(255,colors.z);
		//printf("|x ===> %f|\t|y ==> %f|\t| z ==> %f|\n",colors.x,colors.y,colors.z);
	amcolor = rgbconvert(colors.x,colors.y,colors.z);
/*	amcolor = rgbconvert( min(255, 255 * i_ambient.x) , min(255, 255 * i_ambient.y),min (255,255 *i_ambient.z));
	 amcolor = amcolor + rgbconvert(min(255,i_diffuse.x * 255),min(255,i_diffuse.y * 255 ),min(255,i_diffuse.z * 255));
	 amcolor = amcolor + rgbconvert(min(255,i_specular.x * 255),min(255,i_specular.y * 255),min(255,i_specular.z * 255));*/
	}
	return amcolor;
}