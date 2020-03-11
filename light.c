/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:02:08 by zjamali           #+#    #+#             */
/*   Updated: 2020/03/11 20:43:31 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector ft_specular(t_light *light,t_ray ray,double t,t_object *object)
{
	t_vector scale_direction_to_p = vectorscal(&ray.direction,t);
	t_vector p = vectorsadd(&ray.origin,&scale_direction_to_p);
	t_vector n = vectorsSub(&p,&object->origin);
	n = normalize(&n);
	t_vector from_camera_to_p = vectorscal(&p,-1);
	from_camera_to_p = normalize(&from_camera_to_p);
 	t_vector l_p = vectorsSub(&p,&light->origin); // ////
	l_p = normalize(&l_p);
	double dot = vectorsDot(&l_p,&n);
	t_vector r = vectorscal(&n,dot * 2);
	t_vector reflection = vectorsSub(&r,&l_p);
	reflection = normalize(&reflection);
	dot = vectorsDot(&from_camera_to_p,&reflection);
	double i_specular = pow(dot,2302);
	t_vector color = {light->color.x /255 * i_specular /* * light->intensity */,  i_specular  * light->color.y /255 /* * light->intensity */, light->color.z  * i_specular /255 /* * light->intensity */};

	return color;
}
t_vector ft_diffuse(t_light *light,t_ray ray,double t,t_object *object,t_vector *colors)
{
	// printf("t = %f\n",t);
	t_vector scale_direction_to_P = vectorscal(&ray.direction,t);
	// printf("raydirection(%f,%f,%f)\n",ray.direction.x,ray.direction.y,ray.direction.z);
	//t_vector p = scale_direction_to_P;
	t_vector p = vectorsadd(&ray.origin,&scale_direction_to_P); 
	// printf("p->  %f %f %f   \n",p.x , p.y,p.z);
	t_vector n = vectorsSub(&p,&object->origin); /////////
	n = normalize(&n);
	// printf("n->  %f %f %f   \n",n.x , n.y,n.z);
	t_vector l_p;
	l_p = vectorsSub(&light->origin,&p);

	t_vector p_c = vectorsSub(&ray.origin,&p);
	p_c = normalize(&p_c);
	// printf("l->  %f %f %f   \n",l_p.x , l_p.y,l_p.z);
	l_p = normalize(&l_p);
	// printf("lno->  %f %f %f   \n",l_p.x , l_p.y,l_p.z);
	double i_diffuse = vectorsDot(&l_p,&n);
	printf(" diffuse   %f   \n",i_diffuse);
	//i_diffuse = i_diffuse / 100;
	printf("diffuse  = %f   \n",i_diffuse);
	//i_diffuse = max(0,i_diffuse);
	t_vector color = { colors->x / 255 *light->color.x /255 * light->intensity * i_diffuse ,
	colors->y  /255* light->intensity  * i_diffuse  * light->color.y /255,colors->z /255 * light->color.z /225 * light->intensity * i_diffuse};
	return color;
}
t_vector ft_ambient(t_ambient *ambient,t_vector *color)
{
	//double i_total; //i_total = i_ambient + i_diffuse + i_specular
	t_vector i_ambient = {ambient->intensity * color->x /255,
	ambient->intensity * color->y /255 , ambient->intensity * color->z /255};
	i_ambient.x = min(1, i_ambient.x);
	i_ambient.y = min(1, i_ambient.y);
	i_ambient.z = min(1, i_ambient.z);
	//printf("  %f %f %f   \n",i_ambient.x , i_ambient.y,i_ambient.z);
	return i_ambient;
}