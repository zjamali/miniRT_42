/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 01:04:46 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/16 18:49:32 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_print_error(char *error)
{
	write(2, "Error\n", 6);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

double		rgbconvert(int ir, int ig, int ib)
{
	return (ir * 65536 + ig * 256 + ib);
}

t_pixel		int_color_to_pixel(int color)
{
	t_pixel pixel;

	pixel.b = color % 256;
	pixel.g = color / 256 % 256;
	pixel.r = color / 256 / 256 % 256;
	return (pixel);
}

t_ray		*ft_ray_creating(t_scene *scene, t_camera *camera, int i, int j)
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	ray->origin = camera->lookfrom;
	ray->direction = ft_camera_ray(scene, camera, i, j);
	ray->direction = normalize(ray->direction);
	return (ray);
}

void		ft_render(t_scene *scene, t_camera *camera, int n)
{
	int i;
	int j;
	int k;

	k = scene->resolution.height - 1;
	j = 0;
	if (n == 1)
		ft_creat_image_pixels_array(scene);
	while (j < scene->resolution.height)
	{
		i = 0;
		while (i < scene->resolution.width)
		{
			scene->ray = ft_ray_creating(scene, camera, i, j);
			scene->color_of_pixel = ft_color_of_pixel(scene);
			if (n == 1)
				scene->pixels[k][i] = int_color_to_pixel(scene->color_of_pixel);
			if (n == 0)
				my_mlx_pixel_put(scene->img, i, j, scene->color_of_pixel);
			i++;
		}
		j++;
		k--;
	}
}
