/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:59:10 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/23 16:47:10 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj_properties	ft_parsing_sphere_properties(char **sph, t_scene *scene)
{
	t_obj_properties obj;

	if (sph[3] == NULL)
	{
		ft_print_error(scene, "you have to specify the sphere center \
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

t_obj_properties	ft_parsing_plan_properties(char **pl, t_scene *scene)
{
	t_obj_properties obj;

	if (pl[3] == NULL)
		ft_print_error(scene, "you have to specify the plan coordination\
				point,orientation and color.");
	obj.origin = ft_split(pl[1], ',');
	obj.normal = ft_split(pl[2], ',');
	obj.color = ft_split(pl[3], ',');
	return (obj);
}

void				parsing_plan(char **pl, t_scene *scene)
{
	t_obj_properties	obj;
	t_plane				*plane;
	t_object			*new_object;

	obj = ft_parsing_plan_properties(pl, scene);
	ft_check_plane(scene, obj);
	if (!(plane = (t_plane*)malloc(sizeof(t_plane))))
		ft_print_error(scene, "allocation error");
	ft_memset((void*)plane, 0, sizeof(t_plane));
	plane->coord = ft_parse_coord(obj.origin);
	plane->orientation = ft_parse_normal(obj.normal);
	plane->color = ft_parse_color(obj.color);
	if (!(new_object = (t_object*)malloc(sizeof(t_object))))
		ft_print_error(scene, "allocation error");
	ft_memset((void*)new_object, 0, sizeof(t_object));
	new_object->object_type = 'p';
	new_object->object = plane;
	new_object->origin = plane->coord;
	new_object->orientation = plane->orientation;
	new_object->color = plane->color;
	new_object->next = NULL;
	ft_lstadd_back(&scene->objects, new_object);
	ft_element_can_transforme(scene, 'p', new_object);
}

t_object			*ft_create_square(t_scene *scene, t_square *square)
{
	t_object *new_object;

	if (!(new_object = (t_object*)malloc(sizeof(t_object))))
		ft_print_error(scene, "allocation error");
	ft_memset((void*)new_object, 0, sizeof(t_object));
	new_object->object_type = 'q';
	new_object->object = square;
	new_object->origin = square->center;
	new_object->orientation = square->normal;
	new_object->size = square->edge_size;
	new_object->color = square->color;
	new_object->next = NULL;
	return (new_object);
}

void				parsing_square(char **sqr, t_scene *scene)
{
	t_obj_properties	obj;
	t_square			*square;
	t_object			*new_object;

	if (sqr[4] == NULL)
		ft_print_error(scene, "you have to specify the square center \
		coordination point,orientation,edge size and color.");
	obj.origin = ft_split(sqr[1], ',');
	obj.normal = ft_split(sqr[2], ',');
	obj.color = ft_split(sqr[4], ',');
	obj.size = ft_atod(sqr[3]);
	ft_check_square(scene, obj);
	if (!(square = (t_square*)malloc(sizeof(t_square))))
		ft_print_error(scene, "allocation error");
	ft_memset((void*)square, 0, sizeof(t_square));
	square->edge_size = obj.size;
	square->center = ft_parse_coord(obj.origin);
	square->normal = ft_parse_normal(obj.normal);
	square->color = ft_parse_color(obj.color);
	new_object = ft_create_square(scene, square);
	ft_lstadd_back(&scene->objects, new_object);
	ft_element_can_transforme(scene, 'q', new_object);
}
