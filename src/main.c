/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:24:02 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/13 12:06:23 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "errno.h"
#include "string.h"


int check_camera_inside_an_object(t_camera *camera,t_object *object);

void ft_putchar(char c)
{
	write(1,&c,1);
}

t_ray *ft_ray_creating(t_scene *scene,t_camera *camera,int i,int j)
{
	t_ray *ray;
	ray = malloc(sizeof(t_ray));
	ray->origin = camera->lookfrom;
	ray->direction = ft_camera_ray(scene,camera,i,j); 
	ray->direction = normalize(ray->direction);
	return ray;
}
void            my_mlx_pixel_put(t_imag *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(int*)dst = color;
}
t_imag *ft_creat_img(t_scene *scene,void *mlx_ptr)
{
	t_imag *imag;

	imag = malloc(sizeof(t_imag));
	imag->img = mlx_new_image(mlx_ptr, scene->resolution.width,
	scene->resolution.height);
	imag->addr = mlx_get_data_addr(imag->img, &imag->bits_per_pixel,
	&imag->line_length,&imag->endian);
	return imag;
}

t_scene *ft_scene_init(char *file_name)
{
	extern int errno;
	t_scene *scene;

	scene = malloc(sizeof(t_scene));
	scene->fd = open(file_name,O_RDONLY);
	if (scene->fd < 0)
	{
		ft_print_error(strerror(errno));
		exit(EXIT_FAILURE);
	}
	scene->resolution.height = 0;
	scene->resolution.width = 0;
	scene->ambient.intensity = -1;
	scene->camera = NULL;
	scene->light = NULL;
	scene->objects = NULL;
	scene->img = NULL;
	scene->element_to_transform = NULL;
	return scene;
}

t_pixel int_color_to_pixel(int color)
{
	t_pixel pixel;
	//pixel = malloc(sizeof(t_pixel));

	pixel.b = color % 256;
	pixel.g = color / 256 % 256;
	pixel.r = color / 256 / 256 % 256;

	return pixel;
}
void ft_render(t_scene *scene,t_camera *camera,int n)
{
	int i;
	int j;
	int k;
	k = scene->resolution.height - 1;
	j = 0;
	if (n == 1)
	{
		i = 0;
		scene->pixels = malloc(sizeof(t_pixel*) * scene->resolution.height);
		while (i < scene->resolution.height)
			scene->pixels[i++] = malloc(sizeof(t_pixel) * scene->resolution.width);
	}
	while(j < scene->resolution.height)
	{
		i = 0;
		while(i < scene->resolution.width)
		{
			scene->ray = ft_ray_creating(scene,camera,i,j);
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

t_camera *ft_wich_camera(t_scene *scene,int keycode)
{
	static t_camera *cam;
	if (cam == NULL)
		cam = scene->camera;
	if (keycode == 124 && cam->next != NULL)
		cam = cam->next;
	if (keycode == 123 && cam->prev != NULL)
		cam = cam->prev;
	return cam;
}
int ft_key_press(int keycode,t_scene *scene)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 123 || keycode == 124)
	{
		t_camera *camera;
		camera = ft_wich_camera(scene,keycode);
		ft_render(scene,camera,0);
		mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr,
			scene->img->img, 0, 0);
	}
	return 0;
}

/*****************************/


void ft_write_bmp(t_scene *scene);

int ft_close(t_scene *scene)
{
	(void)scene;
	exit(0);
}

int main(int argc, char **argv)
{
	t_scene *scene;
	
    if(argc > 1)
	{
		scene = ft_scene_init(argv[1]);
		scene = parsing(scene->fd,scene);
		if (argc == 2)
		{
			scene->mlx_ptr = mlx_init();
			scene->win_ptr = mlx_new_window(scene->mlx_ptr,
			scene->resolution.width,scene->resolution.height,argv[1]);
			scene->img = ft_creat_img(scene,scene->mlx_ptr);
			ft_render(scene,scene->camera,0);
			mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr,scene->img->img, 0, 0);
			mlx_hook(scene->win_ptr, 2,0, ft_key_press,scene);
			mlx_hook(scene->win_ptr,17,0,ft_close,scene); /// red button
			mlx_loop(scene->mlx_ptr);
		}
		if (argc > 2 && !ft_strncmp(argv[2] , "--save",7)) /// save 
		{
			ft_render(scene,scene->camera,1);
			ft_write_bmp(scene);
		}
	}
	return 0;
}


/**************** BMP image ******************/

void ft_write_header(/*unsigned char *header,*/t_bmp *image,t_scene *scene)
{
	image->header[0] = 66; /// 'B'
	image->header[1] = 77; /// 'M'
	image->header[10] = 54;
	image->header[14] = 40;  /// iamge header size must at least 40 
	image->header[26] = 1; /// number of planes
	image->header[28] = 24; /// bpp
	image->pixelBytesPerRow = scene->resolution.width*sizeof(t_pixel);
	image->paddingBytesPerRow = (4-(image->pixelBytesPerRow%4))%4;
    image->sizeOfFileEntry = (unsigned int*) &image->header[2];
    image->widthEntry = (unsigned int*) &image->header[18];
    image->heightEntry = (unsigned int*) &image->header[22];
    *image->sizeOfFileEntry = 54 + (image->pixelBytesPerRow+image->paddingBytesPerRow)*scene->resolution.height;  
    *image->widthEntry = scene->resolution.width;
    *image->heightEntry = scene->resolution.height;
}

//supply an array of pixels[height][width] <- notice that height comes first
void ft_write_bmp(t_scene *scene)
{
	t_bmp *image;
	
	image = malloc(sizeof(t_bmp));
	ft_write_header(image,scene);  /// writing header 
	image->fd = open("image.bmp", O_WRONLY|O_CREAT|O_TRUNC,
		S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
	write(image->fd,image->header,54);
	image->zeroes[0] = 0;
	image->zeroes[1] = 0;
	image->zeroes[2] = 0; //{0,0,0}; //for padding
	image->row = 0;
    while (image->row < scene->resolution.height) {
		write(image->fd,scene->pixels[image->row],image->pixelBytesPerRow);
        write(image->fd,image->zeroes,image->paddingBytesPerRow);
		image->row++;
    }
    close(image->fd);
}