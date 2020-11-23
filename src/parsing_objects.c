/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:24:04 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/23 16:45:58 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*ft_create_triangle(t_scene *scene, t_triangle *triangle)
{
	t_object *new_object;

	if (!(new_object = (t_object*)malloc(sizeof(t_object))))
		ft_print_error(scene, "allocation error");
	ft_memset((void*)new_object, 0, sizeof(t_object));
	new_object->object = triangle;
	new_object->color = triangle->color;
	new_object->object_type = 't';
	new_object->v3[0] = triangle->vectors[0];
	new_object->v3[1] = triangle->vectors[1];
	new_object->v3[2] = triangle->vectors[2];
	new_object->next = NULL;
	return (new_object);
}

void		parsing_triangle(char **tr, t_scene *scene)
{
	t_obj_properties	obj;
	t_triangle			*triangle;
	t_object			*new_object;

	if (tr[4] == NULL)
		ft_print_error(scene, "you have to specify 3 trangle\
										points and its color.");
	obj.cord1 = ft_split(tr[1], ',');
	obj.cord2 = ft_split(tr[2], ',');
	obj.cord3 = ft_split(tr[3], ',');
	obj.color = ft_split(tr[4], ',');
	ft_check_triangle(scene, obj);
	if (!(triangle = (t_triangle*)malloc(sizeof(t_triangle))))
		ft_print_error(scene, "allocation error");
	ft_memset((void*)triangle, 0, sizeof(t_triangle));
	triangle->vectors[0] = ft_parse_coord(obj.cord1);
	triangle->vectors[1] = ft_parse_coord(obj.cord2);
	triangle->vectors[2] = ft_parse_coord(obj.cord3);
	triangle->color = ft_parse_color(obj.color);
	new_object = ft_create_triangle(scene, triangle);
	ft_lstadd_back(&scene->objects, new_object);
	ft_element_can_transforme(scene, 't', new_object);
}

t_object	*ft_create_cylinder(t_scene *scene, t_cylinder *cylinder)
{
	t_object *new_object;

	if (!(new_object = (t_object*)malloc(sizeof(t_object))))
		ft_print_error(scene, "allocation error");
	ft_memset((void*)new_object, 0, sizeof(t_object));
	new_object->object = cylinder;
	new_object->color = cylinder->color;
	new_object->object_type = 'c';
	new_object->origin = cylinder->coord;
	new_object->orientation = cylinder->normal;
	new_object->size = cylinder->height;
	new_object->diameter = cylinder->diameter;
	new_object->next = NULL;
	return (new_object);
}

void		parsing_cylinder(char **cy, t_scene *scene)
{
	t_obj_properties	obj;
	t_cylinder			*cylinder;
	t_object			*new_object;

	if (cy[5] == NULL)
		ft_print_error(scene, "you have to specify cylinder coordination points\
		,orientation,diametre,size and color.");
	obj.origin = ft_split(cy[1], ',');
	obj.normal = ft_split(cy[2], ',');
	obj.color = ft_split(cy[5], ',');
	obj.diameter = ft_atod(cy[3]);
	obj.size = ft_atod(cy[4]);
	ft_check_cylinder(scene, obj);
	if (!(cylinder = (t_cylinder*)malloc(sizeof(t_cylinder))))
		ft_print_error(scene, "allocation error");
	ft_memset((void*)cylinder, 0, sizeof(t_cylinder));
	cylinder->coord = ft_parse_coord(obj.origin);
	cylinder->normal = ft_parse_normal(obj.normal);
	cylinder->color = ft_parse_color(obj.color);
	cylinder->diameter = obj.diameter;
	cylinder->height = obj.size;
	new_object = ft_create_cylinder(scene, cylinder);
	ft_lstadd_back(&scene->objects, new_object);
	ft_element_can_transforme(scene, 'y', new_object);
}
