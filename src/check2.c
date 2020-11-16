/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:31:33 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/16 14:34:30 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_check_plane(t_obj_properties obj)
{
	if (ft_check_coords(obj.origin))
		ft_print_error("coordinates of the plan  x,y,z");
	if (ft_check_normal(obj.normal))
		ft_print_error(" normalized orientation vector of plan it's \
		axis in range [0,1]");
	if (ft_check_color(obj.color))
		ft_print_error("plan color in range [0,255]");
}

void	ft_check_sphere(t_obj_properties obj)
{
	if (ft_check_coords(obj.origin))
		ft_print_error("coordinates of the sphere  x,y,z");
	if (ft_check_color(obj.color))
		ft_print_error("sphere color in range [0,255]");
	if (obj.diameter < 0)
		ft_print_error("shpere diameter must be positive");
}

void	ft_check_square(t_obj_properties obj)
{
	if (ft_check_coords(obj.origin))
		ft_print_error("coordinates of the squqre  x,y,z");
	if (ft_check_color(obj.color))
		ft_print_error("square color in range [0,255]");
	if (obj.size < 0)
		ft_print_error("shpere edge size must be positive");
	if (ft_check_normal(obj.normal))
		ft_print_error(" normalized orientation vector of square \
		it's axis in range [0,1]");
}

void	ft_check_triangle(t_obj_properties obj)
{
	if (ft_check_coords(obj.cord1))
		ft_print_error("first coordinates of the traingle  x,y,z");
	if (ft_check_coords(obj.cord2))
		ft_print_error("second coordinates of the traingle  x,y,z");
	if (ft_check_coords(obj.cord2))
		ft_print_error("third coordinates of the traingle  x,y,z");
	if (ft_check_color(obj.color))
		ft_print_error("trangle color in range [0,255]");
}

void	ft_check_cylinder(t_obj_properties obj)
{
	if (ft_check_coords(obj.origin))
		ft_print_error("coordinates of the cylinder  x,y,z");
	if (ft_check_normal(obj.normal))
		ft_print_error(" normalized orientation vector of cylinder \
		it's axis in range [0,1]");
	if (ft_check_color(obj.color))
		ft_print_error("cylinder color in range [0,255]");
	if (obj.size < 0)
		ft_print_error("cyliner height size must be positive");
	if (obj.diameter < 0)
		ft_print_error("cylinder diameter must be positive");
}
