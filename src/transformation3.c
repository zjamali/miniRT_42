/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:49:01 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/16 20:50:32 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector		*ft_calcule_rotaion_x_axis(double angle, t_vector *orientation)
{
	t_vector *new_orientaion;

	new_orientaion = malloc(sizeof(t_vector));
	angle = angle * PI / 180;
	new_orientaion->y = orientation->y * cos(angle) -
											orientation->z * sin(angle);
	new_orientaion->z = orientation->y * sin(angle) +
											orientation->z * cos(angle);
	new_orientaion->x = orientation->x;
	return (new_orientaion);
}

t_vector		*ft_calcule_rotaion_y_axis(double angle, t_vector *orientation)
{
	t_vector *new_orientaion;

	new_orientaion = malloc(sizeof(t_vector));
	angle = angle * PI / 180;
	new_orientaion->z = orientation->z * cos(angle) -
											orientation->x * sin(angle);
	new_orientaion->x = orientation->z * sin(angle) +
											orientation->x * cos(angle);
	new_orientaion->y = orientation->y;
	return (new_orientaion);
}

t_vector		*ft_calcule_rotaion_z_axis(double angle, t_vector *orientation)
{
	t_vector *new_orientaion;

	new_orientaion = malloc(sizeof(t_vector));
	angle = angle * PI / 180;
	new_orientaion->x = orientation->x * cos(angle) -
											orientation->y * sin(angle);
	new_orientaion->y = orientation->x * sin(angle) +
											orientation->y * cos(angle);
	new_orientaion->z = orientation->z;
	return (new_orientaion);
}
