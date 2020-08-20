/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:24:02 by zjamali           #+#    #+#             */
/*   Updated: 2020/03/14 18:21:01 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



void            my_mlx_pixel_put(t_imag *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(int*)dst = color;
}

int main(){
	int W = 1080;
	int H = 720;
	int i,j;
	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr,W,H,"window");

	/***********************/
	t_sphere sphere;
	sphere.origin.x = 0;
	sphere.origin.y = 0;
	sphere.origin.z = -14;
	sphere.radius = 2; //2
	t_vector color ={230,57,70};
	sphere.color = color;

	t_sphere s1;
	s1.origin.x = 4;
	s1.origin.y = 0;
	s1.origin.z = -20;
	s1.radius = 3.5;
	t_vector color2 ={87,205,196};
	s1.color = color2;

	t_sphere s2;
	s2.origin.x = 0;//-3.2;
	s2.origin.y = 20; // 0
	s2.origin.z = -10;//-10;
	s2.radius = 3;// 1.6
	t_vector color1 ={255,166,43};
	s2.color = color1;

	t_sphere s3;
	s3.origin.x = 0;
	s3.origin.y = 0;//3.5;
	s3.origin.z = 25;//-10;
	s3.radius = 3; // 1.5
	t_vector color3 ={0,255,255};
	s3.color = color3;
/***********************************************/

	t_plane plane;
	t_vector cord = {0,-10,-20}; /// 0 -10 0
	
	plane.coord = cord;
	t_vector v = {0,1,0}; /// 010
	plane.orientation = v;
	plane.color.x = 255;
	plane.color.y = 255;
	plane.color.z = 255;
/***********************************************/

	/***********************/
	t_triangle tr;
	tr.vectors[0].x = -1;
	tr.vectors[0].y = -1;
	tr.vectors[0].z = 0;
	tr.vectors[1].x = 1;
	tr.vectors[1].y = -1;
	tr.vectors[1].z = 0;
	tr.vectors[2].x = 0;
	tr.vectors[2].y = 1;
	tr.vectors[2].z = 0;
	t_vector trcolore = {255,0,0};
	tr.color = trcolore;

	/***********************/
	t_camera camera;
	camera.lookfrom.x = 0;//0;  //// 10
	camera.lookfrom.y = 0;//0;  ///// 8
	camera.lookfrom.z = 0;//0;
	camera.fov = 90;
	camera.orientaion.x = 0;
	camera.orientaion.y = 0; //0
	camera.orientaion.z = -1; // -1
	/***********************/

	/***********************/
	t_square sq;
	sq.center.x = 0;
	sq.center.y = 3;
	sq.center.z = 20;
	sq.edge_size = 5;
	t_vector normal = {0,0,-1}; // 1
	sq.normal = normal;
	t_vector sqcolor = {0,255,0};
	sq.color = sqcolor;
	/***********************/

	/***********************/
	t_cylinder cy;
	cy.coord.x = 0;
	cy.coord.y = 0;
	cy.coord.z = -2;

	cy.diameter = 1;
	cy.height = 1;
	cy.normal.x = -1;
	cy.normal.y = 0;
	cy.normal.z = 1;
	t_vector cycolor = {255,0,0};
	cy.color = cycolor;

	t_disk cap0;
	cap0.orientation = vectorscal(&cy.normal,-1);
	cap0.orientation = normalize(&cap0.orientation);
	cap0.color = cy.color;
	cap0.radius = cy.diameter / 2.0;
	cap0.coord = cy.coord;

	t_disk cap1;
	cap1.orientation = normalize(&cy.normal);
	cap1.color = cy.color;
	cap1.radius = cy.diameter / 2.0;
	cap1.coord = normalize(&cy.normal);
	cap1.coord = vectorscal(&cap1.coord,cy.height);
	cap1.coord = vectorsadd(&cy.coord,&cap1.coord);
	/***********************/


/**********************************************/
	t_object object9;
	object9.object = &cap1;
	object9.color = &cap1.color;
	object9.object_type = 'd';
	object9.size = cap1.radius;
	object9.orientation = normalize(&cap1.orientation);
	object9.origin = cap1.coord;
	object9.next = NULL;

	t_object object8;
	object8.object = &cap0;
	object8.color = &cap0.color;
	object8.object_type = 'd';
	object8.size = cap0.radius;
	object8.orientation = normalize(&cap0.orientation);
	object8.origin = cap0.coord;
	object8.next = &object9;

	t_object object7;
	object7.object_type = 'c';
	object7.object = &cy;
	object7.origin = cy.coord;
	object7.orientation = cy.normal;
	object7.size = cy.height;
	object7.diameter = cy.diameter;
	object7.color = &cy.color;
	object7.next = &object8;

	t_object object6;
	object6.object_type = 'q';
	object6.object = &sq;
	object6.origin = sq.center;
	object6.orientation = sq.normal;
	object6.size = sq.edge_size;
	object6.color = &sq.color;
	object6.next = &object7; /// object7 ///////////////////////////////////////


	t_object object5;
	object5.object = &tr;
	object5.color = &tr.color;
	object5.object_type = 't';
	object5.v3[0] = tr.vectors[0];
	object5.v3[1] = tr.vectors[1];
	object5.v3[2] = tr.vectors[2];
	object5.color = &tr.color;
	object5.next = &object6; /////////////////////////

	t_object object4;
	object4.object = &plane;
	object4.color = &plane.color;
	object4.object_type = 'p';
	object4.orientation = plane.orientation;
	object4.origin = plane.coord;
	object4.next = &object6; /// object5;

	t_object object3;
	object3.object = &s3;
	object3.color = &s3.color;
	object3.object_type = 's';
	object3.origin = s3.origin;
	object3.next = &object4; // 

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
	ambient.intensity =0.15;

	t_light light;
	t_vector lightcolor = {255,255,255};
	t_vector coord ;
	light.color = lightcolor;
	light.intensity = 0.9;
	light.origin.x = 0; // -10
	light.origin.y = 0;
	light.origin.z = 10; // -10
/***********************************************/


/***************************  image ********************/

t_imag imag;

    imag.img = mlx_new_image(mlx_ptr, W, H);
	imag.addr = mlx_get_data_addr(imag.img, &imag.bits_per_pixel, &imag.line_length,
                                 &imag.endian);
/************************ image   ***********************/



	i = 0;
	int k = 0;
	while(i < W)
	{
		j = 0;
		while(j < H)
		{
			t_ray ray;
			//ray.origin.x = 0;//0;
			//ray.origin.y = 0;//0;
			//ray.origin.z = 5;//0;

			//t_vector v = {0,0,0};
			//ray.direction = v;
			ray.origin = camera.lookfrom;
			ray.direction = ft_camera(camera,H,W,i,j);
			ray.direction = normalize(&ray.direction);
			int colors = ft_color_of_pixel(ray,&object4,&ambient,&light);

			my_mlx_pixel_put(&imag, i, j, colors);

			//img_data[k++] = colors;
			//img_data[j * 8] = rgbconvert(255,255,0);


			//mlx_pixel_put(mlx_ptr,win_ptr,i,j,colors);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, imag.img, 0, 0);
mlx_loop(mlx_ptr);
}