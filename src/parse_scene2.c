/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:35:19 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/24 14:36:09 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		parsing_ambiant(char **amb, t_scene *scene)
{
	char **color;

	if (scene->ambient.intensity != -1)
		ft_print_error(scene, "You can't specify ambient twice.");
	if (amb[1] == NULL || amb[2] == NULL || amb[3] != NULL)
		ft_print_error(scene, "you have to specify just the intensity \
		and color.");
	scene->ambient.intensity = ft_atod(amb[1]);
	color = ft_split(amb[2], ',');
	scene->ambient.color.x = ft_atoi(color[0]);
	scene->ambient.color.y = ft_atoi(color[1]);
	scene->ambient.color.z = ft_atoi(color[2]);
}

void		ft_check_camera(t_scene *scene, char **origin, char **orient)
{
	if (ft_check_coords(origin))
		ft_print_error(scene, "camera lookfrom in coordination x,y,z");
	if (ft_check_normal(orient))
		ft_print_error(scene, "camera orientation in x,y,z");
}

void		parsing_camera(char **cam, t_scene *scene)
{
	char		**origin;
	char		**orient;
	int			fiel_view;
	t_camera	*camera;

	if (cam[1] == NULL || cam[2] == NULL || cam[3] == NULL || cam[4] != NULL)
		ft_print_error(scene, "camera need lookfrom,orientation,field of view");
	origin = ft_split(cam[1], ',');
	orient = ft_split(cam[2], ',');
	fiel_view = ft_atoi(cam[3]);
	ft_check_camera(scene, origin, orient);
	if (!(camera = (t_camera*)malloc(sizeof(t_camera))))
		ft_print_error(scene, "allocation error");
	ft_memset((void*)camera, 0, sizeof(t_camera));
	camera->lookfrom = ft_parse_coord(origin);
	camera->orientaion = ft_parse_normal(orient);
	camera->next = NULL;
	camera->prev = NULL;
	camera->fov = fiel_view;
	if (camera->fov > 180 || camera->fov < 0)
		ft_print_error(scene, "camera is field of view must be between \
				0 and 180");
	ft_lstadd_back_camera(&scene->camera, camera);
	ft_element_can_transforme(scene, 'c', camera);
}

void		parsing_light(char **lit, t_scene *scene)
{
	char		**origin;
	char		**color;
	double		intensity;
	t_light		*light;

	if (lit[1] == NULL || lit[2] == NULL || lit[3] == NULL || lit[4] != NULL)
		ft_print_error(scene, "light need point,brightness and color.");
	origin = ft_split(lit[1], ',');
	color = ft_split(lit[3], ',');
	intensity = ft_atod(lit[2]);
	if (ft_check_coords(origin))
		ft_print_error(scene, "light coordination point x,y,z");
	if (ft_check_color(color))
		ft_print_error(scene, "light color red,green,blue in range [0,255]");
	if (intensity < 0 || intensity > 1)
		ft_print_error(scene, "light britness must be in range [0,1]");
	if (!(light = (t_light*)malloc(sizeof(t_light))))
		ft_print_error(scene, "allocation error");
	light->origin = ft_parse_coord(origin);
	light->color = ft_parse_color(color);
	light->intensity = intensity;
	light->next = NULL;
	ft_lstadd_back_light(&scene->light, light);
	ft_element_can_transforme(scene, 'l', light);
	scene->light_number++;
}
