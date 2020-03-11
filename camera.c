/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:59:10 by zjamali           #+#    #+#             */
/*   Updated: 2020/03/11 20:58:13 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector ft_camera(t_camera camera,double H,double W,double x,double y)
{
	t_vector lookAtPoint = {0,0,-1};
	t_vector lookFrom = {0,0,0};
	t_vector up = {0,1,0};
	t_vector n = vectorsSub(&lookFrom,&lookAtPoint);
	//printf("|x ===> %f|\t|y ===> %f|\t|z ===> %f|\n",n.x,n.y,n.z);
	n = normalize(&n);
	t_vector u = vecttorscross(&up,&n);
	u = normalize(&u);
	t_vector v = vecttorscross(&n,&u);
	double theta = camera.fov*PI/180;
	double aspectRatio = W/H;
	double viewPlaneHalfWidth = aspectRatio * tan(theta/2);
	double viewPlaneHalfHeight= -1 * tan(theta/2);
	//t_vector lookAtPoint = vectorsadd(&camera.orientaion,&camera.lookfrom);
	camera.lookfrom = lookFrom;
	t_vector c = vectorsSub(&camera.lookfrom,&n);
	//printf("|x ===> %f|\t|y ===> %f|\t|z ===> %f|\n",c.x,c.z,c.z);
	
	t_vector l;
	l.x = c.x - u.x * viewPlaneHalfWidth/2 - v.x * viewPlaneHalfHeight /2;
	l.y = c.y - u.y * viewPlaneHalfWidth/2 - v.y * viewPlaneHalfHeight /2;
	l.z = c.z - u.z * viewPlaneHalfWidth/2 - v.z * viewPlaneHalfHeight /2;
	
	// printf("|x ===> %f|\t|y ===> %f|\t|z ===> %f|\n",l.x,l.y,l.z);

	camera.orientaion.x = l.x + u.x * x * viewPlaneHalfWidth/W + v.x * y * viewPlaneHalfHeight/H;
	camera.orientaion.y = l.y + u.y * x * viewPlaneHalfWidth/W + v.y * y * viewPlaneHalfHeight/H;
	camera.orientaion.z = l.z + u.z * x * viewPlaneHalfWidth/W + v.z * y * viewPlaneHalfHeight/H;
	
	// printf("|x ===> %f|\t|y ===> %f|\t|z ===> %f|\n",camera.orientaion.x,camera.orientaion.y,camera.orientaion.z);
	
	// t_vector A = vectorscal(&v,viewPlaneHalfHeight);
	// t_vector B = vectorscal(&u,viewPlaneHalfWidth);
	// t_vector C =  vectorsSub(&lookAtPoint,&A);

	// t_vector viewPlaneBottomLeftPoint = vectorsSub(&C,&B);
	// t_vector xIncVector = vectorscal(&u,2*viewPlaneHalfWidth/W);
	// t_vector yIncVector = vectorscal(&v,2*viewPlaneHalfHeight/H);
	// C = vectorscal(&xIncVector,x);
	// B = vectorscal(&yIncVector,y);
	// A = vectorsadd(&C,&B);

	// t_vector viewPlanePoint = vectorsadd(&viewPlaneBottomLeftPoint,&A);
	 t_vector castRay = camera.orientaion;
	// castRay = vectorsSub(&viewPlanePoint,&camera.lookfrom);
	return castRay;
}