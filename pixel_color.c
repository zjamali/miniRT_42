/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:09:11 by zjamali           #+#    #+#             */
/*   Updated: 2020/03/13 19:10:33 by zjamali          ###   ########.fr       */
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
	t_vector shadow;
	t_object *temp ;
	temp = object;
	while (temp != NULL)
	{
		closet_object1 = hit_sphere(ray,temp->object);
		if (closet_object1 != 0)
		{
			if (closet_object1 < closet_object)
				{
					check = 1;
					closet_object = closet_object1;
					color = *temp->color;
					i_diffuse = ft_diffuse(light,ray,closet_object,temp,&color);
					i_ambient = ft_ambient(ambient,&color);
					i_specular = ft_specular(light,ray,closet_object,temp);
					shadow = ft_shadow(temp,object,light,ray,closet_object);
					colors.y =  i_ambient.y * 255 +  	 i_diffuse.y * 255 +       i_specular.y * 255;
					colors.x =  i_ambient.x * 255 +    	 i_diffuse.x * 255 +       i_specular.x * 255;
					colors.z =  i_ambient.z * 255 + 	 i_diffuse.z * 255 +       i_specular.z * 255;
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
	else
		amcolor = rgbconvert(255,255,255);
	
	return amcolor;
}