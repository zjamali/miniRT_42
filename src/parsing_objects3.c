/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:29:17 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/24 14:30:13 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj_properties	ft_parsing_sphere_properties(char **sph, t_scene *scene)
{
	t_obj_properties obj;

	if (sph[1] == NULL || sph[2] == NULL || sph[3] == NULL || sph[4] != NULL)
	{
		ft_print_error(scene, "you have to specify just the sphere center \
		coordination point,diameter and color.");
	}
	obj.origin = ft_split(sph[1], ',');
	obj.color = ft_split(sph[3], ',');
	obj.diameter = ft_atod(sph[2]);
	return (obj);
}

void				parsing_sphere(char **sph, t_scene *scene)
{
	t_obj_properties	obj;
	t_sphere			*sphere;
	t_object			*new_object;

	obj = ft_parsing_sphere_properties(sph, scene);
	ft_check_sphere(scene, obj);
	if (!(sphere = (t_sphere*)malloc(sizeof(t_sphere))))
		ft_print_error(scene, "alloction error");
	ft_memset((void*)sphere, 0, sizeof(t_sphere));
	sphere->radius = obj.diameter / 2.0;
	sphere->origin = ft_parse_coord(obj.origin);
	sphere->color = ft_parse_color(obj.color);
	if (!(new_object = (t_object*)malloc(sizeof(t_object))))
		ft_print_error(scene, "allocation error");
	ft_memset((void*)new_object, 0, sizeof(t_object));
	new_object->object_type = 's';
	new_object->object = sphere;
	new_object->origin = sphere->origin;
	new_object->color = sphere->color;
	new_object->radius = sphere->radius;
	new_object->next = NULL;
	ft_lstadd_back(&scene->objects, new_object);
	ft_element_can_transforme(scene, 's', new_object);
}
