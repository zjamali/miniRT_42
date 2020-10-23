/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:24:02 by zjamali           #+#    #+#             */
/*   Updated: 2020/10/23 20:43:16 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int check_camera_inside_an_object(t_camera *camera,t_object *object);

void ft_putchar(char c)
{
	write(1,&c,1);
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
		void	*win_ptr = mlx_new_window(mlx_ptr,scene->resolution->width,scene->resolution->height,"window");
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
				t_ray ray;
				ray.origin = scene->camera->lookfrom;
				ray.direction = ft_camera(scene->camera,scene->resolution->height,scene->resolution->width,i,j);
				ray.direction = normalize(&ray.direction);
				if (check_camera_inside_an_object(scene->camera,scene->objects))
					return 0;
				int colors = ft_color_of_pixel(ray,scene->objects,scene->ambient,scene->light);
				my_mlx_pixel_put(&imag, i, j, colors);
				j++;
			}
			i++;
		}
		mlx_put_image_to_window(mlx_ptr, win_ptr, imag.img, 0, 0);
		mlx_loop(mlx_ptr);
	}
}



int check_camera_inside_an_object(t_camera *camera,t_object *object)
{
	//t_vector scale_direction_to_p = vectorscal(&ray.direction,t);
	//t_vector p = vectorsadd(&ray.origin,&scale_direction_to_p);

	//t_vector p_l = vectorsSub(&ray.origin,&p);
	//t_vector p_l = vectorscal(&ray.direction,-1);
	//t_ray p_ray;
	
	//p_ray.origin.y = p.y - 0.000001;
	//p_ray.origin.x = p.x - 0.000001;
	//p_ray.origin.z = p.z - 0.000001;
	//if (ray.direction.x >= 0 && p.x > 0)
	//	p_ray.origin.x = p.x - 0.000001;
	//else
	//	p_ray.origin.x = p.x + 0.000001;
	//if (ray.direction.y >= 0 && p.y > 0)
	//	p_ray.origin.y = p.y - 0.000001;
	//else
	//	p_ray.origin.y = p.y + 0.000001;
	//if (ray.direction.z >= 0 && p.z > 0)
	//	p_ray.origin.z = p.z - 0.000001;
	//else
	//	p_ray.origin.z = p.z + 0.000001;
	///if (p_ray.direction.y < 0)
	///	p_ray.origin.y = p.y - 0.000001;
	///else
	///	p_ray.origin.y = p.y + 0.000001;
	//if (ray.origin.z <= 0)
	//{	
	//	p_ray.origin.x = p.x - 0.000001;
	//	p_ray.origin.y = p.y - 0.000001;
	//	p_ray.origin.z = p.z - 0.000001;
	//}
	//else
	//{
	//	p_ray.origin.x = p.x;// + 0.1;
	//	p_ray.origin.y = p.y;// + 0.1;
	//	p_ray.origin.z = p.z;// + 0.1;
	//}
	//p_ray.direction = normalize(&p_l);

	//write(1,"hello\n",6);

	t_ray ray;

	ray.direction = camera->orientaion;
	ray.origin = camera->lookfrom;
	t_ray ray1;
	ray1.origin = vectorscal(&ray.origin,1);
	ray1.origin.z = ray.origin.z + 10000000000; /// cam 1
	ray1.direction = vectorsSub(&ray.origin,&ray1.origin);
	ray1.direction = normalize(&ray1.direction);
	t_ray ray2;
	ray2.origin = vectorscal(&ray.origin,1);
	ray2.origin.z = ray.origin.z - 10000000000; /// cam 2
	ray2.direction = vectorsSub(&ray.origin,&ray2.origin);
	ray2.direction = normalize(&ray2.direction);


	double closet_object1_t = 0;
	double closet_object_t = 000000000000;

	t_object *temp;
	temp = object;
	t_object *temp1;
	temp1 = object;
	while (temp != NULL)
	{
		///////////////// p1 
	//	write(1,"hello\n",6);
		if (temp->object_type == 's')
			closet_object1_t = hit_sphere(ray1,temp->object);
		else if (temp->object_type == 'p')
			closet_object1_t = hit_plane(ray1,temp->object);
		else if (temp->object_type == 't')
			closet_object1_t = hit_triangle(ray1,temp->object);
		else if (temp->object_type == 'q')
			closet_object1_t = hit_square(ray1,temp->object);
		else if (temp->object_type == 'c')
			closet_object1_t = hit_cylinder(ray1,temp->object);
		else if (temp->object_type == 'd')
			closet_object1_t = hit_disk(ray1,temp->object);
		if (closet_object1_t <= 0)
			return 0;
		//////////// p2
		if (temp1->object_type == 's')
			closet_object_t = hit_sphere(ray1,temp1->object);
		else if (temp1->object_type == 'p')
			closet_object_t = hit_plane(ray1,temp1->object);
		else if (temp1->object_type == 't')
			closet_object_t = hit_triangle(ray1,temp1->object);
		else if (temp1->object_type == 'q')
			closet_object_t = hit_square(ray1,temp1->object);
		else if (temp1->object_type == 'c')
			closet_object_t = hit_cylinder(ray1,temp1->object);
		else if (temp1->object_type == 'd')
			closet_object_t = hit_disk(ray1,temp1->object);
		if (closet_object_t <= 0)
			return 0;
		write(1,"hello\n",6);
		if (closet_object1_t > 0 && closet_object_t > 0 && temp->object == temp1->object)
		{
			t_vector scale_direction_to_p1 = vectorscal(&ray1.direction,closet_object1_t);
			t_vector p1 = vectorsadd(&ray1.origin,&scale_direction_to_p1);

			t_vector scale_direction_to_p2 = vectorscal(&ray2.direction,closet_object_t);
			t_vector p2 = vectorsadd(&ray2.origin,&scale_direction_to_p2);

			if (p1.x == ray.origin.x && p1.y == ray.origin.y &&
			 	p2.x == ray.origin.x && p2.y == ray.origin.y)
			{
				t_vector o;
				o.x = ray.origin.x;
				o.y = ray.origin.y;
				o.z =  (p1.z + p2.z) / 2;
				
				t_vector o_p1 = vectorsSub(&p1,&o);
				t_vector o_c = vectorsSub(&ray.origin,&o);
				double r = fabs(o.z);
				
				if(fabs(o_c.z) > r)
				{
					//write(1,"hello\n",6);
					return 1;
				}
				else
				{
					return 0;
				}
				
				///r = abs(r) / 2;
			}
			return 0;
		}
			
		temp = temp->next;
		temp1 = temp1->next;
	}
	return 0;
	
}