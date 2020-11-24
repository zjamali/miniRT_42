/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:37:37 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/24 12:29:45 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector		ft_calcule_rotaion(t_vector orientation, t_vector rotaion)
{
	t_vector new_orientation;

	new_orientation.x = orientation.x;
	new_orientation.y = orientation.y;
	new_orientation.z = orientation.z;
	new_orientation = ft_calcule_rotaion_x_axis(rotaion.x, new_orientation);
	new_orientation = ft_calcule_rotaion_y_axis(rotaion.y, new_orientation);
	new_orientation = ft_calcule_rotaion_z_axis(rotaion.z, new_orientation);
	new_orientation = normalize(new_orientation);
	return (new_orientation);
}

void			ft_make_rotation2(t_scene *scene)
{
	t_object	*obj;
	t_plane		*pl;
	t_square	*sq;

	if (scene->element_to_transform->wich_element == 'p')
	{
		obj = scene->element_to_transform->element;
		pl = obj->object;
		obj->orientation = ft_calcule_rotaion(obj->orientation,
		scene->element_to_transform->transform.rot);
		pl->orientation = ft_calcule_rotaion(pl->orientation,
		scene->element_to_transform->transform.rot);
	}
	else if (scene->element_to_transform->wich_element == 'q')
	{
		obj = scene->element_to_transform->element;
		sq = obj->object;
		obj->orientation = ft_calcule_rotaion(obj->orientation,
		scene->element_to_transform->transform.rot);
		sq->normal = ft_calcule_rotaion(sq->normal,
		scene->element_to_transform->transform.rot);
	}
}

void			ft_make_rotation(t_scene *scene)
{
	t_camera	*cam;
	t_cylinder	*cy;
	t_object	*obj;

	if (scene->element_to_transform->wich_element == 'c')
	{
		cam = scene->element_to_transform->element;
		cam->orientaion = ft_calcule_rotaion(cam->orientaion,
		scene->element_to_transform->transform.rot);
	}
	else if (scene->element_to_transform->wich_element == 'y')
	{
		obj = scene->element_to_transform->element;
		cy = obj->object;
		obj->orientation = ft_calcule_rotaion(obj->orientation,
		scene->element_to_transform->transform.rot);
		cy->normal = ft_calcule_rotaion(cy->normal,
		scene->element_to_transform->transform.rot);
	}
	ft_make_rotation2(scene);
	scene->element_to_transform->transform.rot = bzero_vector();
}
