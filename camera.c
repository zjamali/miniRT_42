/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:59:10 by zjamali           #+#    #+#             */
/*   Updated: 2020/03/14 17:54:41 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector ft_camera(t_camera camera,double H,double W,double x,double y)
{
	//t_vector lookAtPoint = {0,0,-10};
	//t_vector lookFrom = {0,5,0};
	t_vector up = {0,1,0};
	//t_vector n = vectorsSub(&lookFrom,&lookAtPoint);   //// camera.orientation
	t_vector n = normalize(&camera.orientaion);
	n = vectorscal(&n,-1);
	//n = normalize(&n);
	t_vector u = vecttorscross(&up,&n);
	u = normalize(&u);
	t_vector v = vecttorscross(&n,&u);
	double theta = camera.fov*PI/180;
	double aspectRatio = W/H;
	double viewPlaneHalfWidth = aspectRatio * tan(theta/2);
	double viewPlaneHalfHeight= -1 * tan(theta/2);
	//camera.lookfrom = lookFrom;
	t_vector none = {0,0,0};
	// *t_vector c = vectorsSub(&camera.lookfrom,&n);
	//t_vector c = vectorsSub(&none,&n);
	t_vector c = vectorscal(&n,-1);
	t_vector l;
	l.x = c.x - u.x * viewPlaneHalfWidth/2 - v.x * viewPlaneHalfHeight /2;
	l.y = c.y - u.y * viewPlaneHalfWidth/2 - v.y * viewPlaneHalfHeight /2;
	l.z = c.z - u.z * viewPlaneHalfWidth/2 - v.z * viewPlaneHalfHeight /2;
	t_vector castRay;
	castRay.x = l.x + u.x * x * viewPlaneHalfWidth/W + v.x * y * viewPlaneHalfHeight/H;
	castRay.y = l.y + u.y * x * viewPlaneHalfWidth/W + v.y * y * viewPlaneHalfHeight/H;
	castRay.z = l.z + u.z * x * viewPlaneHalfWidth/W + v.z * y * viewPlaneHalfHeight/H;
	return castRay;
}