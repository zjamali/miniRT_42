/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 10:06:37 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/18 10:08:09 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_free_scene(t_scene *scene)
{
	if (scene != NULL)
	{
		write(1, "free", 4);
		if (scene->camera != NULL)
			ft_free_cameras(scene->camera);
		if (scene->light != NULL)
			ft_free_lights(scene->light);
		if (scene->objects != NULL)
			ft_free_objects(scene->objects);
		if (scene->img != NULL)
		{
			mlx_destroy_image(scene->mlx_ptr, scene->img->img);
			free(scene->img);
			mlx_clear_window(scene->mlx_ptr, scene->win_ptr);
			mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
		}
		if (scene->pixels != NULL)
			ft_free_pixels(scene);
		if (scene->ray != NULL)
			free(scene->ray);
		if (scene->element_to_transform != NULL)
			free(scene->element_to_transform);
		free(scene);
		scene = NULL;
	}
}

void		ft_free_cameras(t_camera *cam)
{
	t_camera *cameras;
	t_camera *cam_to_free;

	cameras = cam;
	while (cameras != NULL)
	{
		cam_to_free = cameras;
		cameras = cameras->next;
		free(cam_to_free);
		cam_to_free = NULL;
	}
}

void		ft_free_lights(t_light *lights)
{
	t_light *light;
	t_light *light_to_free;

	light = lights;
	while (light != NULL)
	{
		light_to_free = light;
		light = light->next;
		free(light_to_free);
		light_to_free = NULL;
	}
}

void		ft_free_objects(t_object *objects)
{
	t_object *obj;
	t_object *obj_to_free;

	obj = objects;
	while (obj != NULL)
	{
		obj_to_free = obj;
		obj = obj->next;
		free(obj_to_free->object);
		obj_to_free->object = NULL;
		free(obj_to_free);
		obj_to_free = NULL;
	}
}

void		ft_free_pixels(t_scene *scene)
{
	int i;

	i = 0;
	while (i < scene->resolution.height)
	{
		free(scene->pixels[i]);
		scene->pixels[i] = NULL;
		i++;
	}
	free(scene->pixels);
	scene->pixels = NULL;
}
