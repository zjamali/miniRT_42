/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_object                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:31:33 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/20 09:39:09 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_check_plane(t_scene *scene, t_obj_properties obj)
{
	if (ft_check_coords(obj.origin))
		ft_print_error(scene, "coordinates of the plan  x,y,z");
	if (ft_check_normal(obj.normal))
		ft_print_error(scene, " normalized orientation vector of plan it's \
		axis in range [0,1]");
	if (ft_check_color(obj.color))
		ft_print_error(scene, "plan color in range [0,255]");
}

void	ft_check_sphere(t_scene *scene, t_obj_properties obj)
{
	if (ft_check_coords(obj.origin))
		ft_print_error(scene, "coordinates of the sphere  x,y,z");
	if (ft_check_color(obj.color))
		ft_print_error(scene, "sphere color in range [0,255]");
	if (obj.diameter < 0)
		ft_print_error(scene, "shpere diameter must be positive");
}

void	ft_check_square(t_scene *scene, t_obj_properties obj)
{
	if (ft_check_coords(obj.origin))
		ft_print_error(scene, "coordinates of the squqre  x,y,z");
	if (ft_check_color(obj.color))
		ft_print_error(scene, "square color in range [0,255]");
	if (obj.size < 0)
		ft_print_error(scene, "shpere edge size must be positive");
	if (ft_check_normal(obj.normal))
		ft_print_error(scene, " normalized orientation vector of square \
		it's axis in range [0,1]");
}

void	ft_check_triangle(t_scene *scene, t_obj_properties obj)
{
	if (ft_check_coords(obj.cord1))
		ft_print_error(scene, "first coordinates of the traingle  x,y,z");
	if (ft_check_coords(obj.cord2))
		ft_print_error(scene, "second coordinates of the traingle  x,y,z");
	if (ft_check_coords(obj.cord2))
		ft_print_error(scene, "third coordinates of the traingle  x,y,z");
	if (ft_check_color(obj.color))
		ft_print_error(scene, "trangle color in range [0,255]");
}

void	ft_check_cylinder(t_scene *scene, t_obj_properties obj)
{
	if (ft_check_coords(obj.origin))
		ft_print_error(scene, "coordinates of the cylinder  x,y,z");
	if (ft_check_normal(obj.normal))
		ft_print_error(scene, " normalized orientation vector of cylinder \
		it's axis in range [0,1]");
	if (ft_check_color(obj.color))
		ft_print_error(scene, "cylinder color in range [0,255]");
	if (obj.size < 0)
		ft_print_error(scene, "cyliner height size must be positive");
	if (obj.diameter < 0)
		ft_print_error(scene, "cylinder diameter must be positive");
}
