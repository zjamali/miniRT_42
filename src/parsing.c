/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:24:02 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/20 09:28:37 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_make_translatio_cam_light(t_scene *scene)
{
	t_light		*light;
	t_camera	*cam;

	if (scene->element_to_transform->wich_element == 'l')
	{
		light = scene->element_to_transform->element;
		light->origin = vectorsadd(light->origin,
		scene->element_to_transform->transform.trans);
	}
	else if (scene->element_to_transform->wich_element == 'c')
	{
		cam = scene->element_to_transform->element;
		cam->lookfrom = vectorsadd(cam->lookfrom,
		scene->element_to_transform->transform.trans);
	}
}

void		ft_make_translation(t_scene *scene)
{
	ft_make_translatio_cam_light(scene);
	if (scene->element_to_transform->wich_element == 's')
		ft_translate_sphere(scene);
	else if (scene->element_to_transform->wich_element == 'p')
		ft_translate_plane(scene);
	else if (scene->element_to_transform->wich_element == 'q')
		ft_translate_square(scene);
	else if (scene->element_to_transform->wich_element == 't')
		ft_translate_traiangle(scene);
	else if (scene->element_to_transform->wich_element == 'y')
		ft_translate_cylinder(scene);
	scene->element_to_transform->transform.trans = bzero_vector();
}

void		parse_translation(char **line, t_scene *scene)
{
	char	**tran;

	if (line[1] == NULL)
		ft_print_error(scene, "you have to specify the transation coordination");
	else
	{
		tran = ft_split(line[1], ',');
		if (scene->element_to_transform != NULL)
		{
			scene->element_to_transform->transform.trans = ft_parse_coord(tran);
			ft_make_translation(scene);
		}
	}
}

void		parse_rotation(char **line, t_scene *scene)
{
	char **rot;

	if (line[1] == NULL)
		ft_print_error(scene, "you have to specify the rotation angles");
	else
	{
		rot = ft_split(line[1], ',');
		if (scene->element_to_transform != NULL)
		{
			scene->element_to_transform->transform.rot = ft_parse_coord(rot);
			ft_make_rotation(scene);
		}
	}
}

void		parsing_resolution(char **resol, t_scene *scene)
{
	if (scene->resolution.height != 0)
		ft_print_error(scene, "You can't specify resolution twice.");
	if (resol[1] == NULL || resol[2] == NULL)
		ft_print_error(scene, "you have to specify the width and height.");
	scene->resolution.width = ft_atoi(resol[1]);
	scene->resolution.height = ft_atoi(resol[2]);
}
