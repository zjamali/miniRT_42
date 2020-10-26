/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:24:02 by zjamali           #+#    #+#             */
/*   Updated: 2020/10/26 14:08:58 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int check_camera_inside_an_object(t_camera *camera,t_object *object);

void ft_putchar(char c)
{
	write(1,&c,1);
}

t_ray *ft_ray_creating(t_scene *scene,int i,int j)
{
	t_ray *ray;
	ray = malloc(sizeof(t_ray));
	ray->origin = scene->camera->lookfrom;
	ray->direction = ft_camera(scene->camera,scene->resolution->height,scene->resolution->width,i,j);
	ray->direction = normalize(&ray->direction);

	return ray;
}
void            my_mlx_pixel_put(t_imag *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(int*)dst = color;
}

int main(int argc, char **argv)
{
    if(argc > 1)
	{
		t_scene *scene;
		int i;
		int j;
		int fd;

		fd = open(argv[1],O_RDONLY);
		scene = parsing(fd);
		void	*mlx_ptr = mlx_init();
		void	*win_ptr = mlx_new_window(mlx_ptr,scene->resolution->width,scene->resolution->height,argv[1]);
		t_imag imag;
    	imag.img = mlx_new_image(mlx_ptr, scene->resolution->width, scene->resolution->height);
		imag.addr = mlx_get_data_addr(imag.img, &imag.bits_per_pixel, &imag.line_length,
    	                             &imag.endian);
		i = 0;
		while(i < scene->resolution->width)
		{
			j = 0;
			while(j < scene->resolution->height)
			{
				scene->ray = ft_ray_creating(scene,i,j);
				int colors = ft_color_of_pixel(scene);
				my_mlx_pixel_put(&imag, i, j, colors);
				j++;
			}
			i++;
		}
		mlx_put_image_to_window(mlx_ptr, win_ptr, imag.img, 0, 0);
		mlx_loop(mlx_ptr);
	}
}
