/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:24:02 by zjamali           #+#    #+#             */
/*   Updated: 2020/10/30 14:51:56 by zjamali          ###   ########.fr       */
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
	ray->direction = ft_camera_ray(scene,i,j); 
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
/*
int key_press(int keycode,t_scene *scene)
{
	static double x;
	x = 0.5;
	static int wish_object;
	static t_vector *v3;
	//printf("%f\n",scene->objects->origin.x);
	if (keycode == 7)
	{
		v3 = NULL;
		wish_object = 0;
	}
	if (keycode == 53)
	{
		free(scene);
		exit(0);
	}
	if (keycode == 37)//)|| keycode == 8 || keycode == 31)
	{
		x = 5;
		v3 = &scene->light->origin;
		wish_object = 1;
	}
	if (keycode == 8)
	{
		x = 0.5;
		v3 = &scene->camera->lookfrom;
		wish_object = 1;
	}
	if (keycode == 31) // //// objects
	{
		//if (scene->objects->object_type == 's')
		//{
		//	t_sphere *sp;
		//	sp = scene->objects->object;
		//	v3 = &sp->origin;
		//}
		wish_object = 2;
		x = 0.5;
	}
	if (wish_object == 2)
	{
		if (keycode == 1)
	}
	if (wish_object == 1)
	{
		if (keycode == 124) /// right button
			v3->x += x;///scene->light->origin.x += x;
		else if (keycode == 123) /// left button
			v3->x -= x;
		else if (keycode == 126) ///up button
			v3->y += x;
		else if (keycode == 125) /// down button
			v3->y -= x;
		else if (keycode == 13) /// + button
			v3->z += x;
		else if (keycode == 1) /// - button
			v3->z -= x;
		ft_render(scene);
		mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr,	scene->img->img, 0, 0);
	}
	return 0;
}
*/
t_object *ft_select_selected_object(t_scene *scene,char ch)
{
	t_object *temp;
	temp = scene->objects;
	while (temp != NULL)
	{
		if (temp->object_type == ch)
			return temp;
		temp = temp->next;
	}
	return NULL;	
}
t_vector *ft_select_square(t_scene *scene)
{
	static int next;
	t_object *object;
	object = ft_select_selected_object(scene,'q');
	if (object != NULL)
	{
		t_square *sq;
		sq = object->object;
		return &sq->center;
	}
	return NULL;
	
}
t_vector *ft_select_sphere(t_scene *scene)
{
	static int next;
	t_object *object;
	object = ft_select_selected_object(scene,'s');
	if (object != NULL)
	{
		//t_sphere *sp;
		//sp = object->object;
		return &object->origin;
	}
	return NULL;
}

t_vector *ft_select_plan(t_scene *scene)
{
	static int next;
	t_object *object;
	object = ft_select_selected_object(scene,'p');
	if (object != NULL)
	{
		t_plane *p;
		p = object->object;
		return &p->coord;
	}
	return NULL;
}
t_vector *ft_select_cylinder(t_scene *scene)
{
	static int next;
	t_object *object;
	object = ft_select_selected_object(scene,'c');
	if (object != NULL)
	{
		t_cylinder *cy;
		cy = object->object;
		return &object->origin;
	}
	return NULL;
}
/*
t_object *ft_wich_object_to_move(int keycode, t_scene *scene)
{
	static int wich_object;
	static double x;
	t_vector v3;
	static t_object *object;
	if (keycode == 7)
	{ ////  x button
		if (wich_object == 1)
			wich_object = 0;
		v3 = NULL;
	}
	if (keycode == 31)
	{ // //// objects
		v3 = NULL;
		wich_object = 1;
	}
	if (wich_object == 1)
	{
		if (keycode == 1)
			v3 = ft_select_sphere(scene);
		else if (keycode == 12)
			v3 = ft_select_square(scene);
		else if (keycode == 35)
			v3 = ft_select_plan(scene);
		else if (keycode == 16)
			v3 = ft_select_cylinder(scene);	
		else if (keycode == 17)
		{
			
		}
		
	}
	//{
	//	wich_object = 2;
	//if (wich_object == 2)
	//{
	//	if (keycode == 1)
//
	//}
	return v3;
}
*/
t_triangle *ft_select_triangle(t_scene *scene)
{
	t_object *ob;
	ob = ft_select_selected_object(scene,'t');
	t_triangle *tr;
	tr = ob->object; 
	return tr;
}
void ft_move_traingle(t_scene *scene,int keycode)
{
	t_triangle *tr;
	tr = ft_select_triangle(scene);
	
	int x =  1;
	if (tr != NULL)
	{
			if (keycode == 124) /// right button
			{
				write(1,"hh\n",2);
				tr->vectors[0].x  += x;
				tr->vectors[1].x  += x;
				tr->vectors[2].x  += x;
			}
			else if (keycode == 123) /// left button
			{	
				tr->vectors[0].x  -= x;
				tr->vectors[1].x  -= x;
				tr->vectors[2].x  -= x;
			}
			else if (keycode == 126) ///up button
			{	
				tr->vectors[0].y  += x;
				tr->vectors[1].y  += x;
				tr->vectors[2].y  += x;
			}
			else if (keycode == 125) /// down button
			{	
				tr->vectors[0].y  -= x;
				tr->vectors[1].y  -= x;
				tr->vectors[2].y  -= x;
			}
			else if (keycode == 24) /// + button
			{	
				tr->vectors[0].z  += x;
				tr->vectors[1].z  += x;
				tr->vectors[2].z  += x;
			}
			else if (keycode == 27) /// - button
			{	
				tr->vectors[0].z  -= x;
				tr->vectors[1].z  -= x;
				tr->vectors[2].z  -= x;
			}
			ft_render(scene);
			mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr,	scene->img->img, 0, 0);
	}
}
void ft_move_selected_object(int keycode,t_object *object)
{
	
	
}

t_camera *ft_wich_camera(t_scene *scene,int keycode)
{
	int loop;
	loop = keycode - 83;
	t_camera *temp;
	temp = scene->camera;
	printf("%d|%d\n",keycode,loop);
	while (temp != NULL && loop)
	{
		loop--;
		temp = temp->next;
	}
	return temp;
}
/*
int ft_key_press(int keycode,t_scene *scene)
{
	//write(1,"select an object:\n",18);
	static int *keys;
	static int i;
	static int selected;
	t_vector *v3;
	keys = malloc(sizeof(int) * 10);
	if (keycode == 53)
		exit(0);
	if (keycode == 7) /// button x
		selected = 0;
	if (keycode == 37 || keycode == 8 || keycode == 31) // light
			selected = 1;
	else
	{
		if (selected == 1)
		{
			if (keycode == 8)
				selected = 2;
			if (keycode == 37)
				selected = 3;
			if (keycode == 31)
				selected = 4;
		}
		if ()
	}
	
	//else
	//{
	//	t_object *object;
	//	//object = ft_wich_object_to_move(keycode,scene);
	//	ft_move_selected_object(keycode,object);
	//}
	return 0;
}
*/
int main(int argc, char **argv)
{
	int i;
	int j;
	t_scene *scene;
    if(argc > 1)
	{
		scene = ft_scene_init(argv[1]);
		scene = parsing(scene->fd);
		scene->mlx_ptr = mlx_init();
		scene->win_ptr = mlx_new_window(scene->mlx_ptr,
			scene->resolution->width,scene->resolution->height,argv[1]);
		scene->img = ft_creat_img(scene,scene->mlx_ptr,scene->win_ptr);
		ft_render(scene);
		mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr,
			scene->img->img, 0, 0);
		///mlx_hook(scene->win_ptr, 2,0, ft_key_press,scene);
		mlx_loop(scene->mlx_ptr);
	}
}
