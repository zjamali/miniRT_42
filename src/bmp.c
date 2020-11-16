/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:03:17 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/16 11:11:38 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_write_header(t_bmp *image, t_scene *scene)
{
	image->header[0] = 66;
	image->header[1] = 77;
	image->header[10] = 54;
	image->header[14] = 40;
	image->header[26] = 1;
	image->header[28] = 24;
	image->pixelBytesPerRow = scene->resolution.width * sizeof(t_pixel);
	image->paddingBytesPerRow = (4 - (image->pixelBytesPerRow % 4)) % 4;
	image->sizeOfFileEntry = (unsigned int*)&image->header[2];
	image->widthEntry = (unsigned int*)&image->header[18];
	image->heightEntry = (unsigned int*)&image->header[22];
	*image->sizeOfFileEntry = 54 + (image->pixelBytesPerRow +
	image->paddingBytesPerRow) * scene->resolution.height;
	*image->widthEntry = scene->resolution.width;
	*image->heightEntry = scene->resolution.height;
}

void	ft_write_bmp(t_scene *scene)
{
	t_bmp *image;

	image = malloc(sizeof(t_bmp));
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
		write(image->fd, scene->pixels[image->row], image->pixelBytesPerRow);
		write(image->fd, image->zeroes, image->paddingBytesPerRow);
		image->row++;
	}
	close(image->fd);
}

void	ft_creat_image_pixels_array(t_scene *scene)
{
	int i;

	i = 0;
	scene->pixels = malloc(sizeof(t_pixel*) * scene->resolution.height);
	while (i < scene->resolution.height)
	{
		scene->pixels[i] = malloc(sizeof(t_pixel) * scene->resolution.width);
		i++;
	}
}
