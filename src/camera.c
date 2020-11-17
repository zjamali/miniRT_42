/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:59:10 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/17 13:30:24 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera_variables	ft_camera_properties(t_scene *scene, t_camera *camera)
{
	t_camera_variables vbs;

	vbs.w = scene->resolution.width;
	vbs.h = scene->resolution.height;
	vbs.up.x = 0;
	vbs.up.y = 1;
	vbs.up.z = 0;
	if ((camera->orientaion.y > 0 || camera->orientaion.y < 0)
	&& (camera->orientaion.x == 0 && camera->orientaion.z == 0))
	{
		vbs.up.x = 0;
		vbs.up.y = 0;
		vbs.up.z = -1;
	}
	vbs.n = normalize(camera->orientaion);
	vbs.n = vectorscal(vbs.n, -1);
	vbs.n = normalize(vbs.n);
	vbs.u = vecttorscross(vbs.up, vbs.n);
	vbs.u = normalize(vbs.u);
	vbs.v = vecttorscross(vbs.n, vbs.u);
	vbs.v = normalize(vbs.v);
	return (vbs);
}

t_vector			ft_camera_ray(t_scene *scene, t_camera *camera,
					double x, double y)
{
	t_vector			cast_ray;
	t_camera_variables	vbs;

	vbs = ft_camera_properties(scene, camera);
	vbs.theta = camera->fov * PI / 180;
	vbs.aspect_ratio = vbs.w / vbs.h;
	vbs.view_plane_half_width = vbs.aspect_ratio * tan(vbs.theta / 2);
	vbs.view_plane_half_height = -1 * tan(vbs.theta / 2);
	vbs.c = vectorscal(vbs.n, -1);
	vbs.l.x = vbs.c.x - vbs.u.x * vbs.view_plane_half_width / 2 - vbs.v.x *
	vbs.view_plane_half_height / 2;
	vbs.l.y = vbs.c.y - vbs.u.y * vbs.view_plane_half_width / 2 - vbs.v.y *
	vbs.view_plane_half_height / 2;
	vbs.l.z = vbs.c.z - vbs.u.z * vbs.view_plane_half_width / 2 - vbs.v.z *
	vbs.view_plane_half_height / 2;
	cast_ray.x = vbs.l.x + vbs.u.x * x * vbs.view_plane_half_width / vbs.w +
	vbs.v.x * y * vbs.view_plane_half_height / vbs.h;
	cast_ray.y = vbs.l.y + vbs.u.y * x * vbs.view_plane_half_width / vbs.w +
	vbs.v.y * y * vbs.view_plane_half_height / vbs.h;
	cast_ray.z = vbs.l.z + vbs.u.z * x * vbs.view_plane_half_width / vbs.w +
	vbs.v.z * y * vbs.view_plane_half_height / vbs.h;
	return (cast_ray);
}

double		max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double		min(double a, double b)
{
	if (a > b)
		return (b);
	else
		return (a);
}