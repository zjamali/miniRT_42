/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:09:11 by zjamali           #+#    #+#             */
/*   Updated: 2020/03/14 17:46:19 by zjamali          ###   ########.fr       */
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
	t_vector i_specular = {0,0,0};
	t_vector i_diffuse =  {0,0,0};
	t_vector i_ambient =  {0,0,0};
	double shadow;
	t_object *temp ;
	temp = object;
	while (temp != NULL)
	{
		if (temp->object_type == 's')
			closet_object1 = hit_sphere(ray,temp->object);
		else if (temp->object_type == 'p')
			closet_object1 = hit_plane(ray,temp->object);
		else if (temp->object_type == 't')
			closet_object1 = hit_triangle(ray,temp->object);
		else if (temp->object_type == 'q')
			closet_object1 = hit_square(ray,temp->object);
		if (closet_object1 != 0)
		{
			if (closet_object1 < closet_object)
			{
				check = 1;
				closet_object = closet_object1;
				color = *temp->color;
				i_specular = ft_specular(light,ray,closet_object,temp);
				i_diffuse = ft_diffuse(light,ray,closet_object,temp,&color);
				if(temp->object_type == 'p')
				{
					t_vector d = ft_diffuse(light,ray,closet_object,temp,&color);
					i_diffuse = d;
					t_vector s = {0,0,0};
					i_specular = s;
				}
				if(temp->object_type == 't')
				{
					t_vector d = ft_diffuse(light,ray,closet_object,temp,&color);
					i_diffuse = d;
				}
				if(temp->object_type == 'q')
				{
					t_vector d = ft_diffuse(light,ray,closet_object,temp,&color);
					i_diffuse = d;
					t_vector s = {0,0,0};
					i_specular = s;
				}
				i_ambient = ft_ambient(ambient,&color);
				shadow = ft_shadow(temp,object,light,ray,closet_object);
				colors.y =  i_ambient.y * 255 +  shadow *	( i_diffuse.y * 255 +       i_specular.y * 255);
				colors.x =  i_ambient.x * 255 +  shadow *	( i_diffuse.x * 255 +       i_specular.x * 255);
				colors.z =  i_ambient.z * 255 +  shadow *	( i_diffuse.z * 255 +       i_specular.z * 255);
			}
		}
		temp = temp->next;
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