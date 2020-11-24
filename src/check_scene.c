/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:10:33 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/24 13:21:25 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_check_scene(t_scene *scene)
{
	int height;
	int width;

	width = 5120;
	height = 2880;
	if (scene->camera == NULL)
		ft_print_error(scene, "No camera in the scene,you need at least\
		one camera in the scene.");
	if (scene->resolution.height == 0 && scene->resolution.width == 0)
		ft_print_error(scene, "you have to specify just the resolution.");
	if (scene->resolution.height > height)
		scene->resolution.height = height;
	if (scene->resolution.width > width)
		scene->resolution.width = width;
}

int			ft_check_color(char **color)
{
	t_vector colors;

	if (color[0] == NULL || color[1] == NULL || color[2] == NULL)
		return (1);
	else
	{
		colors = ft_parse_color(color);
		if (colors.x < 0 || colors.x > 255 || colors.y < 0 || colors.y > 255 ||
				colors.z < 0 || colors.z > 255)
			return (1);
	}
	return (0);
}

int			ft_check_coords(char **coord)
{
	if (coord[0][0] == ' ' || coord[1] != NULL)
		return (0);
	if (coord[0] == NULL || coord[1] == NULL || coord[2] == NULL)
		return (1);
	return (0);
}
