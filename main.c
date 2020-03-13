/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:24:02 by zjamali           #+#    #+#             */
/*   Updated: 2020/03/13 18:32:55 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(){
	int H = 1080;
	int W = 1080;
	int i,j;
	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr,W,H,"test");

	/***********************/
	t_sphere sphere;
	sphere.origin.x = 0;
	sphere.origin.y = 0;
	sphere.origin.z = -10;
	sphere.radius = 1.5;
	t_vector color ={255,0,0};
	sphere.color = color;

	t_sphere s1;
	s1.origin.x = 3.2;
	s1.origin.y = 0;
	s1.origin.z = -10;
	s1.radius = 1.5;
	t_vector color2 ={0,0,255};
	s1.color = color2;

	t_sphere s2;
	s2.origin.x = -3.2;
	s2.origin.y = 0;
	s2.origin.z = -10;
	s2.radius = 1.5;
	t_vector color1 ={255,255,0};
	s2.color = color1;

	t_sphere s3;
	s3.origin.x = 0;
	s3.origin.y = 3.2;
	s3.origin.z = -10;
	s3.radius = 1.5;
	t_vector color3 ={0,255,255};
	s3.color = color3;



	/***********************/


	/***********************/
	t_camera camera;
	// camera.lookfrom.x = 0;
	// camera.lookfrom.y = 0;
	// camera.lookfrom.z = 5;
	camera.fov = 90;
	// camera.orientaion.x = 0;
	// camera.orientaion.y = 0;
	// camera.orientaion.z = -1;
	/***********************/
    i = 0;

/**********************************************/
	t_object object3;
	object3.object = &s3;
	object3.color = &s3.color;
	object3.object_type = 's';
	object3.origin = s3.origin;
	object3.next = NULL;

	t_object object2;
	object2.object = &sphere;
	object2.color = &sphere.color;
	object2.object_type = 's';
	object2.origin = sphere.origin;
	object2.next = &object3;

	t_object object1;
	object1.object = &s2;
	object1.color = &s2.color;
	object1.object_type = 's';
	object1.origin = s2.origin;
	object1.next = &object2;
 
	t_object object;
	object.object = &s1;
	object.color = &s1.color;
	object.object_type = 's';
	object.origin = s1.origin;
	object.next = &object1;
/***********************************************/

	t_ambient ambient;
	//t_vector ambcolor = {255,255,255};
	//ambient.color = ambcolor;
	ambient.intensity =0.1;

	t_light light;
	t_vector lightcolor = {255,255,255};
	t_vector coord ;
	light.color = lightcolor;
	light.intensity = 0.5;
	light.origin.x = 0;
	light.origin.y = 0;
	light.origin.z = 0;

/***********************************************/
	while(i < W)
	{
		j = 0;
		while( j < H)
		{
			t_ray ray;
			ray.origin.x = 0;
			ray.origin.y = 0;
			ray.origin.z = 0;

			t_vector v = {0,0,0};
			ray.direction = v;
			ray.direction = ft_camera(camera,H,W,i,j);
			//printf("ray->direction(%f,%f,%f)\n",ray.direction.x,ray.direction.y,ray.direction.z);
			ray.direction = normalize(&ray.direction);
			t_vector color = {255,255,255};
			int colors = ft_color_of_pixel(ray,&object,&ambient,&light);
			mlx_pixel_put(mlx_ptr,win_ptr,i,j,colors);
			j++;
		}
		i++;
	}
mlx_loop(mlx_ptr);
}