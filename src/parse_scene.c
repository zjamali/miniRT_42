/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:50:46 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/16 19:23:25 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		parsing_ambiant(char **amb, t_scene *scene)
{
	char **color;

	if (scene->ambient.intensity != -1)
		ft_print_error("You can't specify ambient twice.");
	if (amb[1] == NULL || amb[2] == NULL)
		ft_print_error("you have to specify the intensity and color.");
	scene->ambient.intensity = ft_atof(amb[1]);
	color = ft_split(amb[2], ',');
	scene->ambient.color.x = ft_atoi(color[0]);
	scene->ambient.color.y = ft_atoi(color[1]);
	scene->ambient.color.z = ft_atoi(color[2]);
}

void		parsing_camera(char **cam, t_scene *scene)
{
	char		**origin;
	char		**orient;
	int			fiel_view;
	t_camera	*camera;

	if (cam[3] == NULL)
		ft_print_error("camera need lookfrom,orientation and field of view");
	origin = ft_split(cam[1], ',');
	orient = ft_split(cam[2], ',');
	fiel_view = ft_atoi(cam[3]);
	if (ft_check_coords(origin))
		ft_print_error("camera lookfrom in coordination x,y,z");
	if (ft_check_normal(orient))
		ft_print_error("camera orientation in x,y,z");
	camera = malloc(sizeof(t_camera));
	camera->lookfrom = ft_parse_coord(origin);
	camera->orientaion = ft_parse_normal(orient);
	camera->next = NULL;
	camera->prev = NULL;
	camera->fov = fiel_view;
	if (camera->fov > 180 || camera->fov < 0)
		ft_print_error("camera is field of view must be between \
				0 and 180");
	ft_lstadd_back_camera(&scene->camera, camera);
	ft_element_can_transforme(scene, 'c', camera);
}

void		parsing_light(char **light_line, t_scene *scene)
{
	char		**origin;
	char		**color;
	double		intensity;
	t_light		*light;

	if (light_line[3] == NULL)
		ft_print_error("you have to specify the light \
				coordination point,brightness and color.");
	origin = ft_split(light_line[1], ',');
	color = ft_split(light_line[3], ',');
	intensity = ft_atof(light_line[2]);
	if (ft_check_coords(origin))
		ft_print_error("light coordination point x,y,z");
	if (ft_check_color(color))
		ft_print_error("light color red,green,blue in range [0,255]");
	if (intensity < 0 || intensity > 1)
		ft_print_error("light britness must be in range [0,1]");
	light = malloc(sizeof(t_light));
	light->origin = ft_parse_coord(origin);
	light->color = ft_parse_color(color);
	light->intensity = intensity;
	light->next = NULL;
	ft_lstadd_back_light(&scene->light, light);
	ft_element_can_transforme(scene, 'l', light);
}

void		parsing_line(char *line, t_scene *scene)
{
	char **split;

	split = ft_split(line, ' ');
	if (split[0][0] == 'R')
		parsing_resolution(split, scene);
	else if (split[0][0] == 'A')
		parsing_ambiant(split, scene);
	else if (split[0][0] == 'l')
		parsing_light(split, scene);
	else if (ft_strncmp(split[0], "c", 2) == 0)
		parsing_camera(split, scene);
	else if (ft_strncmp(split[0], "pl", 2) == 0)
		parsing_plan(split, scene);
	else if (ft_strncmp(split[0], "sp", 2) == 0)
		parsing_sphere(split, scene);
	else if (ft_strncmp(split[0], "sq", 2) == 0)
		parsing_square(split, scene);
	else if (ft_strncmp(split[0], "tr", 3) == 0)
		parsing_triangle(split, scene);
	else if (ft_strncmp(split[0], "cy", 2) == 0)
		parsing_cylinder(split, scene);
	else if (ft_strncmp(split[0], "tra", 3) == 0)
		parse_translation(split, scene);
	else if (ft_strncmp(split[0], "rot", 3) == 0)
		parse_rotation(split, scene);
}

t_scene		*parsing(int fd, t_scene *scene)
{
	char *line;

	while (get_next_line(fd, &line) > 0)
	{
		if (line[0])
		{
			if (ft_check_line(line))
				parsing_line(line, scene);
			free(line);
		}
	}
	if (line[0])
	{
		if (ft_check_line(line))
			parsing_line(line, scene);
		free(line);
	}
	ft_check_scene(scene);
	return (scene);
}