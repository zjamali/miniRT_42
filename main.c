/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:24:02 by zjamali           #+#    #+#             */
/*   Updated: 2020/10/27 12:38:15 by zjamali          ###   ########.fr       */
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
	ray->direction = ft_camera(scene->camera,scene->resolution->height,
		scene->resolution->width,i,j);
	ray->direction = normalize(&ray->direction);
	return ray;
}
void            my_mlx_pixel_put(t_imag *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(int*)dst = color;
}
t_imag *ft_creat_img(t_scene *scene,void *mlx_ptr,void *win_ptr)
{
	t_imag *imag;
	imag = malloc(sizeof(t_imag));
	imag->img = mlx_new_image(mlx_ptr, scene->resolution->width,
	scene->resolution->height);
	imag->addr = mlx_get_data_addr(imag->img, &imag->bits_per_pixel,
	&imag->line_length,&imag->endian);
	return imag;
}

t_scene *ft_scene_init(char *file_name)
{
	t_scene *scene;
	scene = malloc(sizeof(t_scene));
	scene->fd = open(file_name,O_RDONLY);
	return scene;
}

void ft_render(t_scene *scene)
{
	int i;
	int j;
	
	i = 0;
	while(i < scene->resolution->width)
	{
		j = 0;
		while(j < scene->resolution->height)
		{
			scene->ray = ft_ray_creating(scene,i,j);
			scene->color_of_pixel = ft_color_of_pixel(scene);
			my_mlx_pixel_put(scene->img, i, j, scene->color_of_pixel);
			j++;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	int i;
	int j;
	t_scene *scene;
    if(argc > 1)
	{
		scene = ft_scene_init(argv[1]);
		scene = parsing(scene->fd);
		scene->mlx_ptr =mlx_init();
		scene->win_ptr = mlx_new_window(scene->mlx_ptr,
			scene->resolution->width,scene->resolution->height,argv[1]);
		scene->img = ft_creat_img(scene,scene->mlx_ptr,scene->win_ptr);
		ft_render(scene);
		mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr,
			scene->img->img, 0, 0);
		mlx_loop(scene->mlx_ptr);
	}
}
