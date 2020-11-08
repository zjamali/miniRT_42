/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:24:02 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/07 20:51:08 by zjamali          ###   ########.fr       */
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
	return scene;
}

void ft_render(t_scene *scene,t_camera *camera)
{
	int i;
	int j;

	i = 0;
	while(i < scene->resolution.width)
	{
		j = 0;
		while(j < scene->resolution.height)
		{
			scene->ray = ft_ray_creating(scene,camera,i,j);
			scene->color_of_pixel = ft_color_of_pixel(scene);
			my_mlx_pixel_put(scene->img, i, j, scene->color_of_pixel);
			j++;
		}
		i++;
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
		ft_render(scene,camera);
		mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr,
			scene->img->img, 0, 0);
	}
	return 0;
}

/*****************************/
typedef struct s_pixel {
    unsigned char b;
    unsigned char g;
    unsigned char r;
	unsigned char a;
}t_pixel;

void  make_image(t_scene *scene);

int main(int argc, char **argv)
{
	t_scene *scene;
	
    if(argc > 1)
	{
		scene = ft_scene_init(argv[1]);
		scene = parsing(scene->fd,scene);
		scene->mlx_ptr = mlx_init();
		scene->win_ptr = mlx_new_window(scene->mlx_ptr,
			scene->resolution.width,scene->resolution.height,argv[1]);
		scene->img = ft_creat_img(scene,scene->mlx_ptr);
		ft_render(scene,scene->camera);
		mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr,
			scene->img->img, 0, 0);
		mlx_hook(scene->win_ptr, 2,0, ft_key_press,scene);
		make_image(scene);
		mlx_loop(scene->mlx_ptr);
	}
	return 0;
}


/**************** BMP image ******************/


//supply an array of pixels[height][width] <- notice that height comes first
int writeBMP(char* filename,  int width,  int height,int *pixel)
{
    int fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);  
    static unsigned char header[54] = {66,77,0,0,0,0,0,0,0,0,54,0,0,0,40,0,0,0,0,0,0,0,0,0,0,0,1,0,32}; //rest is zeroes
    unsigned int pixelBytesPerRow = width*sizeof(t_pixel);
    unsigned int paddingBytesPerRow = (4-(pixelBytesPerRow%4))%4;
    unsigned int* sizeOfFileEntry = (unsigned int*) &header[2];
    *sizeOfFileEntry = 54 + (pixelBytesPerRow+paddingBytesPerRow)*height;  
    unsigned int* widthEntry = (unsigned int*) &header[18];    
    *widthEntry = width;
    unsigned int* heightEntry = (unsigned int*) &header[22];    
    *heightEntry = height;    
    write(fd, header, 54);
    static unsigned char zeroes[3] = {0,0,0}; //for padding
	int row;
	row = 0;
	int *rgb ;
	rgb = malloc(width*sizeof(int));
	//int i = 0;
	//while (i <= width )
	//{
	//	rgb[i] = rgbconvert(0,0,255);
	//	i++;
	//}
	//
	
    while (row < height) {
		//write(0,pixels[row],pixelBytesPerRow);
		rgb = &pixel[row];
		write(fd,rgb,pixelBytesPerRow);
        write(fd,zeroes,paddingBytesPerRow);
		row++;
    }
    close(fd);
    return 0;
}

void make_image(t_scene *scene)
{
	//int height = scene->resolution.height;
	//int width = scene->resolution.width;
	//t_pixel pixel[height][width];
	int i = 0;
	int j = 0;
	int height = scene->resolution.height;
	int width  = scene->resolution.width;
	//int pixel[height][width];
	char *image_add;
	int line_lenght;
	int bits_per_pixel;
	bits_per_pixel = scene->img->bits_per_pixel;
	line_lenght = scene->img->line_length;
	image_add = scene->img->addr;
	char *dst;
	int color;
	while(j < height)
	{
		while (i < width)
		{
			dst = image_add + ( j * line_lenght + i );
			color = *(int*)dst;
			//mlx_pixel_put(scene->mlx_ptr,scene->win_ptr,i,j * line_lenght,color);
			i++;
		}
		j++;
	}
	
	//writeBMP("image.bmp" ,scene->resolution.width ,scene->resolution.height,*pixel);
}

