/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:59:10 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/13 12:03:38 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector ft_camera_ray(t_scene *scene,t_camera *camera,double x,double y)
{
	t_vector castRay;
	t_camera_variables vbs;

	vbs.W = scene->resolution.width;
	vbs.H = scene->resolution.height;
	vbs.up.x = 0;
	vbs.up.y = 1;
	vbs.up.z = 0;
	if ((camera->orientaion.y > 0 || camera->orientaion.y < 0)  
	&& (camera->orientaion.x == 0  && camera->orientaion.z == 0))
	{//// up vector must be propendiculare  to camera orintation
		vbs.up.x = 0;
		vbs.up.y = 0;
		vbs.up.z = 1;
	}
	vbs.n = normalize(camera->orientaion);
	vbs.n = vectorscal(vbs.n,-1);
	vbs.n = normalize(vbs.n);
	vbs.u = vecttorscross(vbs.up,vbs.n);
	vbs.u = normalize(vbs.u);
	vbs.v = vecttorscross(vbs.n,vbs.u);
	vbs.v = normalize(vbs.v);
	vbs.theta = camera->fov*PI/180;
	vbs.aspectRatio = vbs.W/vbs.H;
	vbs.viewPlaneHalfWidth = vbs.aspectRatio * tan(vbs.theta/2);
	vbs.viewPlaneHalfHeight= -1 * tan(vbs.theta/2);
	vbs.c = vectorscal(vbs.n,-1);
	vbs.l.x = vbs.c.x - vbs.u.x * vbs.viewPlaneHalfWidth/2 - vbs.v.x * vbs.viewPlaneHalfHeight /2;
	vbs.l.y = vbs.c.y - vbs.u.y * vbs.viewPlaneHalfWidth/2 - vbs.v.y * vbs.viewPlaneHalfHeight /2;
	vbs.l.z = vbs.c.z - vbs.u.z * vbs.viewPlaneHalfWidth/2 - vbs.v.z * vbs.viewPlaneHalfHeight /2;
	castRay.x = vbs.l.x + vbs.u.x * x * vbs.viewPlaneHalfWidth/vbs.W + vbs.v.x * y * vbs.viewPlaneHalfHeight/vbs.H;
	castRay.y = vbs.l.y + vbs.u.y * x * vbs.viewPlaneHalfWidth/vbs.W + vbs.v.y * y * vbs.viewPlaneHalfHeight/vbs.H;
	castRay.z = vbs.l.z + vbs.u.z * x * vbs.viewPlaneHalfWidth/vbs.W + vbs.v.z * y * vbs.viewPlaneHalfHeight/vbs.H;
	return castRay;
}