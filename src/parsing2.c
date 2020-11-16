/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:00:56 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/16 20:03:26 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_check_normal(char **norm)
{
	t_vector normal;

	if (norm[0] == NULL || norm[1] == NULL || norm[2] == NULL)
		return (1);
	else
	{
		normal.x = ft_atof(norm[0]);
		normal.y = ft_atof(norm[1]);
		normal.z = ft_atof(norm[2]);
		if (normal.x < -1 || normal.x > 1 || normal.y < -1 || normal.y > 1 ||
				normal.z < -1 || normal.z > 1)
			return (1);
		if (normal.x == 0 && normal.y == 0 && normal.z == 0)
			return (1);
	}
	return (0);
}

t_vector	ft_parse_normal(char **norm)
{
	t_vector normal;

	normal.x = ft_atof(norm[0]);
	normal.y = ft_atof(norm[1]);
	normal.z = ft_atof(norm[2]);
	normal = normalize(normal);
	return (normal);
}

t_vector	ft_parse_color(char **colors)
{
	t_vector color;

	color.x = ft_atoi(colors[0]);
	color.y = ft_atoi(colors[1]);
	color.z = ft_atoi(colors[2]);
	return (color);
}

t_vector	ft_parse_coord(char **coord)
{
	t_vector coords;

	coords.x = ft_atof(coord[0]);
	coords.y = ft_atof(coord[1]);
	coords.z = ft_atof(coord[2]);
	return (coords);
}

void		ft_element_can_transforme(t_scene *scene, char wich_element,
			void *the_element)
{
	if (scene->element_to_transform == NULL)
		scene->element_to_transform = malloc(sizeof(t_element_to_transform));
	scene->element_to_transform->wich_element = wich_element;
	scene->element_to_transform->element = the_element;
}
