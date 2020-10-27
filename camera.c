/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:59:10 by zjamali           #+#    #+#             */
/*   Updated: 2020/10/27 13:26:24 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector ft_camera_ray(t_scene *scene,double x,double y)
{
	t_vector castRay;
	t_vector up;
	t_vector n;
	t_vector u;
	t_vector c;
	t_vector l;
	t_vector v;
	
	double theta;
	double aspectRatio;
	double viewPlaneHalfWidth;
	double viewPlaneHalfHeight;
	
	double W = scene->resolution->width;
	double H = scene->resolution->height;
	
	up.x = 0;
	up.y = 1;
	up.z = 0;
	n = normalize(&scene->camera->orientaion);
	n = vectorscal(&n,-1);
	n = normalize(&n);
	u = vecttorscross(&up,&n);
	u = normalize(&u);
	v = vecttorscross(&n,&u);
	theta = scene->camera->fov*PI/180;
	aspectRatio = W/H;
	viewPlaneHalfWidth = aspectRatio * tan(theta/2);
	viewPlaneHalfHeight= -1 * tan(theta/2);
	c = vectorscal(&n,-1);
	l.x = c.x - u.x * viewPlaneHalfWidth/2 - v.x * viewPlaneHalfHeight /2;
	l.y = c.y - u.y * viewPlaneHalfWidth/2 - v.y * viewPlaneHalfHeight /2;
	l.z = c.z - u.z * viewPlaneHalfWidth/2 - v.z * viewPlaneHalfHeight /2;
	castRay.x = l.x + u.x * x * viewPlaneHalfWidth/W + v.x * y * viewPlaneHalfHeight/H;
	castRay.y = l.y + u.y * x * viewPlaneHalfWidth/W + v.y * y * viewPlaneHalfHeight/H;
	castRay.z = l.z + u.z * x * viewPlaneHalfWidth/W + v.z * y * viewPlaneHalfHeight/H;
	return castRay;
	
	
}