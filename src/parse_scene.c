/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:50:46 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/23 17:09:31 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		parsing_ambiant(char **amb, t_scene *scene)
{
	char **color;

	if (scene->ambient.intensity != -1)
		ft_print_error(scene, "You can't specify ambient twice.");
	if (amb[1] == NULL || amb[2] == NULL || amb[3] != NULL)
		ft_print_error(scene, "you have to specify the intensity and color.");
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

	if (cam[3] == NULL || cam[4] != NULL)
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

void		parsing_light(char **light_line, t_scene *scene)
{
	char		**origin;
	char		**color;
	double		intensity;
	t_light		*light;

	if (light_line[3] == NULL)
		ft_print_error(scene, "light need point,brightness and color.");
	origin = ft_split(light_line[1], ',');
	color = ft_split(light_line[3], ',');
	intensity = ft_atod(light_line[2]);
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

void		parsing_line_objects(t_scene *scene, char **split)
{
	if (ft_strncmp(split[0], "pl", 2) == 0)
		parsing_plan(split, scene);
	else if (ft_strncmp(split[0], "sp", 2) == 0)
		parsing_sphere(split, scene);
	else if (ft_strncmp(split[0], "sq", 2) == 0)
		parsing_square(split, scene);
	else if (ft_strncmp(split[0], "tr", 3) == 0)
		parsing_triangle(split, scene);
	else if (ft_strncmp(split[0], "cy", 2) == 0)
		parsing_cylinder(split, scene);
}

void		ft_spaces_after_comma(char *line, int i, int j)
{
	if (line[i] == ',' && line[i + 1] == ' ')
	{
		j = i + 1;
		while (line[j] == ' ')
		{
			line[j] = '0';
			j++;
		}
		if (line[j] == '-')
		{
			line[i + 1] = '-';
			line[j] = '0';
		}
	}
}

char		*ft_remake_line(char *line)
{
	int i;
	int j;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\t' || line[i] == '\n' ||
			line[i] == '\v' || line[i] == '\f' || line[i] == '\r')
			line[i] = ' ';
		i++;
	}
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' && line[i + 1] == ',')
		{
			j = i;
			while (line[j] == ' ')
				line[j--] = '.';
		}
		ft_spaces_after_comma(line, i, j);
		i++;
	}
	return (line);
}

int			ft_check_cordinations(char *line)
{
	int i;
	int	a;

	i = 0;
	a = 0;
	while (line[i])
	{
		if (line[i] == ',')
			a++;
		i++;
	}
	if (a > 2)
		return (1);
	if (a == 1)
		return (2);
	return (0);
}

int			ft_check_properties(t_scene *scene, char **line)
{
	int i;
	int result;

	i = 0;
	result = 1;
	while (line[i])
	{
		result = ft_check_cordinations(line[i]);
		if (result == 1)
			ft_print_error(scene, "too much coordination");
		if (result == 2)
			ft_print_error(scene, "missing coodinations");
		i++;
	}
	return (0);
}

void		parsing_line(char *line, t_scene *scene)
{
	char **split;

	line = ft_remake_line(line);
	write(1, line, ft_strlen(line));
	write(1, "\n", 1);
	split = ft_split(line, ' ');
	if (split[1] == NULL)
		ft_print_error(scene, "empty coordination");
	ft_check_properties(scene, split);
	if (split[0][0] == 'R')
		parsing_resolution(split, scene);
	else if (split[0][0] == 'A')
		parsing_ambiant(split, scene);
	else if (split[0][0] == 'l')
		parsing_light(split, scene);
	else if (ft_strncmp(split[0], "c", 2) == 0)
		parsing_camera(split, scene);
	else if (ft_strncmp(split[0], "tra", 3) == 0)
		parse_translation(split, scene);
	else if (ft_strncmp(split[0], "rot", 3) == 0)
		parse_rotation(split, scene);
	parsing_line_objects(scene, split);
}

t_scene		*parsing(int fd, t_scene *scene)
{
	char *line;

	while (get_next_line(fd, &line) > 0)
	{
		if (line[0])
		{
			if (ft_check_line(scene, line))
			{
				parsing_line(line, scene);
			}
			if (line != NULL)
				free(line);
		}
	}
	if (line[0])
	{
		if (ft_check_line(scene, line))
			parsing_line(line, scene);
		free(line);
	}
	ft_check_scene(scene);
	return (scene);
}
