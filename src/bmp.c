/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:03:17 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/18 10:06:10 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_make_image(t_scene *scene)
{
	ft_render(scene, scene->camera, 1);
	ft_write_bmp(scene);
	ft_free_pixels(scene);
}

void		ft_write_header(t_bmp *image, t_scene *scene)
{
	image->header[0] = 66;
	image->header[1] = 77;
	image->header[10] = 54;
	image->header[14] = 40;
	image->header[26] = 1;
	image->header[28] = 24;
	image->pixel_bytes_per_row = scene->resolution.width * sizeof(t_pixel);
	image->padding_bytes_per_row = (4 - (image->pixel_bytes_per_row % 4)) % 4;
	image->size_of_file_entry = (unsigned int*)&image->header[2];
	image->width_entry = (unsigned int*)&image->header[18];
	image->height_entry = (unsigned int*)&image->header[22];
	*image->size_of_file_entry = 54 + (image->pixel_bytes_per_row +
	image->padding_bytes_per_row) * scene->resolution.height;
	*image->width_entry = scene->resolution.width;
	*image->height_entry = scene->resolution.height;
}

void		ft_write_bmp(t_scene *scene)
{
	t_bmp *image;

	image = (t_bmp*)malloc(sizeof(t_bmp));
	if (!image)
		ft_print_error(scene,"allocation error");
	ft_memset((void*)image, 0, sizeof(t_bmp));
	ft_write_header(image, scene);
	image->fd = open("image.bmp", O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	write(image->fd, image->header, 54);
	image->zeroes[0] = 0;
	image->zeroes[1] = 0;
	image->zeroes[2] = 0;
	image->row = 0;
	while (image->row < scene->resolution.height)
	{
		write(image->fd, scene->pixels[image->row], image->pixel_bytes_per_row);
		write(image->fd, image->zeroes, image->padding_bytes_per_row);
		image->row++;
	}
	close(image->fd);
	free(image);
}

void		ft_creat_image_pixels_array(t_scene *scene)
{
	int i;

	i = 0;
	scene->pixels = (t_pixel**)malloc(sizeof(t_pixel*) *
								scene->resolution.height);
	while (i < scene->resolution.height)
	{
		scene->pixels[i] = (t_pixel*)malloc(sizeof(t_pixel) *
								scene->resolution.width);
		i++;
	}
}
