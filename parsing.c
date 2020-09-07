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

t_object *ft_lstlast(t_object *lst)
{	
	if(lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
		return (lst);
	}
	return (NULL);
}

void ft_lstadd_back(t_object **alst, t_object *new)
{
	if(*alst)
	{
		t_object *temp;
		temp = ft_lstlast(*alst);
		temp->next = new;
		new->next = NULL;
	}
	else
		*alst = new;
}

t_light *ft_lstlast_light(t_light *lst)
{	
	if(lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
		return (lst);
	}
	return (NULL);
}

void ft_lstadd_back_light(t_light **alst, t_light *new)
{
	if(*alst)
	{
		t_light *temp;
		temp = ft_lstlast_light(*alst);
		temp->next = new;
		new->next = NULL;
	}
	else
		*alst = new;
}

t_camera *ft_lstlast_camera(t_camera *lst)
{	
	if(lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
		return (lst);
	}
	return (NULL);
}

void ft_lstadd_back_camera(t_camera **alst, t_camera *new)
{
	if(*alst)
	{
		t_camera *temp;
		temp = ft_lstlast_camera(*alst);
		temp->next = new;
		new->next = NULL;
	}
	else
		*alst = new;
}

void parsing_resolution(char **resol,t_scene *scene)
{
    t_resolution *resolution;
    resolution = malloc(sizeof(t_resolution));
    resolution->width = ft_atoi(resol[1]);
    resolution->height = ft_atoi(resol[2]);
    scene->resolution = resolution;
}

void parsing_ambiant(char **amb,t_scene *scene)
{
    t_ambient *ambient;
    char **color;
    ambient = malloc(sizeof(t_ambient));
    ambient->intensity = ft_atof(amb[1]);
    color  = ft_split(amb[2],',');
    ambient->color.x = ft_atoi(color[0]);
    ambient->color.y = ft_atoi(color[1]);
    ambient->color.z = ft_atoi(color[2]);

    scene->ambient = ambient;
}

void parsing_camera(char **cam,t_scene *scene)
{
    char **origin;
    char **normal;

    t_camera *camera;
    camera = malloc(sizeof(t_camera));

    origin  = ft_split(cam[1],',');
    camera->lookfrom.x = ft_atof(origin[0]);
    camera->lookfrom.y = ft_atof(origin[1]);
    camera->lookfrom.z = ft_atof(origin[2]);

    normal  = ft_split(cam[2],',');
    camera->orientaion.x = ft_atof(normal[0]);
    camera->orientaion.y = ft_atof(normal[1]);
    camera->orientaion.z = ft_atof(normal[2]); 
    camera->next = NULL;   

    camera->fov = ft_atoi(cam[3]);

    //scene->camera = camera;
    ft_lstadd_back_camera(&scene->camera,camera);
}

void parsing_light(char ** lit,t_scene *scene)
{
    char **origin;
    char **color;

    t_light *light;

    light = malloc(sizeof(t_light));

    origin  = ft_split(lit[1],',');
    light->origin.x = ft_atof(origin[0]);
    light->origin.y = ft_atof(origin[1]);
    light->origin.z = ft_atof(origin[2]);
    light->intensity = ft_atof(lit[2]);

    color  = ft_split(lit[3],',');
    light->color.x = ft_atoi(color[0]);
    light->color.y = ft_atoi(color[1]);
    light->color.z = ft_atoi(color[2]);
    light->next = NULL;

    //scene->light = light;
    ft_lstadd_back_light(&scene->light,light);
}

void parsing_plan(char **pl,t_scene *scene)
{
    char **origin;
    char **normal;
    char **color;

    t_plane *plane;

    plane = malloc(sizeof(t_plane));

    origin  = ft_split(pl[1],',');
    plane->coord.x = ft_atof(origin[0]);
    plane->coord.y = ft_atof(origin[1]);
    plane->coord.z = ft_atof(origin[2]);
    
    normal  = ft_split(pl[2],',');
    plane->orientation.x = ft_atof(normal[0]);
    plane->orientation.y = ft_atof(normal[1]);
    plane->orientation.z = ft_atof(normal[2]); 

    color  = ft_split(pl[3],',');
    plane->color.x = ft_atoi(color[0]);
    plane->color.y = ft_atoi(color[1]);
    plane->color.z = ft_atoi(color[2]);


    t_object *new_object;
    new_object = malloc(sizeof(t_object));

    new_object->object_type = 'p';
    new_object->object = plane;
    new_object->origin = plane->coord;
    new_object->orientation = plane->orientation;
    new_object->color = &plane->color;
    new_object->next = NULL;


    ft_lstadd_back(&scene->objects,new_object);
    //printf("%f,%f,%f  %f,%f,%f  %f,%f,%f\n",plane->coord.x,plane->coord.y,plane->coord.z,
						//plane->orientation.x,plane->orientation.y,plane->orientation.z,
                        //plane->color.x,plane->color.y,plane->color.z);
/*    if (scene->first_object == NULL)
    {
        scene->first_object = new_object;
        scene->objects = new_object;
        scene->objects->next = NULL;
    }
    else
        scene->objects->next= new_object;
*/
    //printf("%f,%f,%f  %f,%f,%f  %f,%f,%f\n",scene->objects->origin.x,scene->objects->origin.y,scene->objects->origin.z,
						//scene->objects->orientation.x,scene->objects->orientation.y,scene->objects->orientation.z,
                        //scene->objects->color->x,scene->objects->color->y,scene->objects->color->z);
}

void parsing_sphere(char **sph,t_scene *scene)
{
    char **origin;
    char **color;

    t_sphere *sphere;

    sphere = malloc(sizeof(t_sphere));

    origin  = ft_split(sph[1],',');
    sphere->origin.x = ft_atof(origin[0]);
    sphere->origin.y = ft_atof(origin[1]);
    sphere->origin.z = ft_atof(origin[2]);
    
    sphere->radius  = ft_atof(sph[2]);

    color  = ft_split(sph[3],',');
    sphere->color.x = ft_atoi(color[0]);
    sphere->color.y = ft_atoi(color[1]);
    sphere->color.z = ft_atoi(color[2]);


    t_object *new_object;
    new_object = malloc(sizeof(t_object));

    new_object->object_type = 's';
    new_object->object = sphere;
    new_object->origin = sphere->origin;
    new_object->color = &sphere->color;
    new_object->next = NULL;
/*
    if (scene->first_object == NULL)
    {
        scene->first_object = new_object;
        scene->objects = new_object;
        new_object->next = NULL;
    }
    else
        objects->next= new_object;
*/
    ft_lstadd_back(&scene->objects,new_object);
}

void parsing_square(char **sqr,t_scene *scene)
{
    char **origin;
    char **color;
    char **normal;

    t_square *square;

    square = malloc(sizeof(t_square));

    origin  = ft_split(sqr[1],',');
    square->center.x = ft_atof(origin[0]);
    square->center.y = ft_atof(origin[1]);
    square->center.z = ft_atof(origin[2]);

    normal  = ft_split(sqr[2],',');
    square->normal.x = ft_atof(normal[0]);
    square->normal.y = ft_atof(normal[1]);
    square->normal.z = ft_atof(normal[2]);
    
    square->edge_size  = ft_atof(sqr[3]);

    color  = ft_split(sqr[4],',');
    square->color.x = ft_atoi(color[0]);
    square->color.y = ft_atoi(color[1]);
    square->color.z = ft_atoi(color[2]);

    t_object *new_object;
    new_object = malloc(sizeof(t_object));

    new_object->object_type = 'q';
    new_object->object = square;
    new_object->origin = square->center;
    new_object->orientation = square->normal;
    new_object->size = square->edge_size;
    new_object->color = &square->color;
    new_object->next = NULL;
/*
    if (scene->first_object == NULL)
    {
        scene->first_object = new_object;
        scene->objects = new_object;
        scene->objects->next = NULL;
    }
    else
        scene->objects = new_object;
*/
    ft_lstadd_back(&scene->objects,new_object);
}

void parsing_triangle(char **tr,t_scene *scene)
{
    char **cord1;
    char **cord2;
    char **cord3;
    char **color;

    t_triangle *triangle;

    triangle = malloc(sizeof(t_triangle));

    cord1  = ft_split(tr[1],',');
    triangle->vectors[0].x = ft_atof(cord1[0]);
    triangle->vectors[0].y = ft_atof(cord1[1]);
    triangle->vectors[0].z = ft_atof(cord1[2]);
    
    cord2  = ft_split(tr[2],',');
    triangle->vectors[1].x = ft_atof(cord2[0]);
    triangle->vectors[1].y = ft_atof(cord2[1]);
    triangle->vectors[1].z = ft_atof(cord2[2]);
    cord3  = ft_split(tr[3],',');
    triangle->vectors[2].x = ft_atof(cord3[0]);
    triangle->vectors[2].y = ft_atof(cord3[1]);
    triangle->vectors[2].z = ft_atof(cord3[2]);
    
    color  = ft_split(tr[4],',');
    triangle->color.x = ft_atoi(color[0]);
    triangle->color.y = ft_atoi(color[1]);
    triangle->color.z = ft_atoi(color[2]);

    t_object *new_object;
    new_object = malloc(sizeof(t_object));

    new_object->object = triangle;
	new_object->color = &triangle->color;
	new_object->object_type = 't';
	new_object->v3[0] = triangle->vectors[0];
	new_object->v3[1] = triangle->vectors[1];
	new_object->v3[2] = triangle->vectors[2];
    new_object->next = NULL;

    ft_lstadd_back(&scene->objects,new_object);
}

void parsing_cylinder(char **cy,t_scene *scene)
{
    char **coord;
    char **normal;
    char **color;

    t_cylinder *cylinder;
    cylinder = malloc(sizeof(t_cylinder));
    coord  = ft_split(cy[1],',');
    cylinder->coord.x = ft_atof(coord[0]);
    cylinder->coord.y = ft_atof(coord[1]);
    cylinder->coord.z = ft_atof(coord[2]);
    normal  = ft_split(cy[2],',');
    cylinder->normal.x = ft_atof(normal[0]);
    cylinder->normal.y = ft_atof(normal[1]);
    cylinder->normal.z = ft_atof(normal[2]);
    color  = ft_split(cy[5],',');
    cylinder->color.x = ft_atoi(color[0]);
    cylinder->color.y = ft_atoi(color[1]);
    cylinder->color.z = ft_atoi(color[2]);

    cylinder->diameter = ft_atof(cy[3]);
    cylinder->height = ft_atof(cy[4]);

    t_disk *cap0;
    cap0 = malloc(sizeof(t_disk));
    cap0->orientation = vectorscal(&cylinder->normal,-1);
	cap0->orientation = normalize(&cap0->orientation);
	cap0->color = cylinder->color;
	cap0->radius = cylinder->diameter / 2.0;
	cap0->coord = cylinder->coord;
    
    t_disk *cap1;
    cap1 = malloc(sizeof(t_disk));
	cap1->orientation = normalize(&cylinder->normal);
	cap1->color = cylinder->color;
	cap1->radius = cylinder->diameter / 2.0;
	cap1->coord = normalize(&cylinder->normal);
	cap1->coord = vectorscal(&cap1->coord,cylinder->height);
	cap1->coord = vectorsadd(&cylinder->coord,&cap1->coord);



    t_object *new_object;
    new_object = malloc(sizeof(t_object));
    new_object->object = cylinder;
	new_object->color = &cylinder->color;
	new_object->object_type = 'c';
    new_object->origin = cylinder->coord;
    new_object->orientation = cylinder->normal;
    new_object->size = cylinder->height;
    new_object->diameter = cylinder->diameter;
    new_object->next = NULL;

    ft_lstadd_back(&scene->objects,new_object);

    t_object *new_object1;
    new_object1 = malloc(sizeof(t_object));
    new_object1->object = cap0;
	new_object1->color = &cap0->color;
	new_object1->object_type = 'd';
    new_object1->origin = cap0->coord;
    new_object1->orientation = normalize(&cap0->orientation);
    new_object1->size = cap0->radius;
    new_object1->next = NULL;
    ft_lstadd_back(&scene->objects,new_object1);
    
    t_object *new_object2;
    new_object2 = malloc(sizeof(t_object));
    new_object2->object = cap1;
	new_object2->color = &cap1->color;
	new_object2->object_type = 'd';
    new_object2->origin = cap1->coord;
    new_object2->orientation = normalize(&cap1->orientation);
    new_object2->size = cap1->radius;
    new_object2->next = NULL;
    ft_lstadd_back(&scene->objects,new_object2);
}
void parsing_line(char *line,t_scene *scene)
{
    char **split;
    split = ft_split(line, ' ');
    if (split[0][0] == 'R')
        parsing_resolution(split,scene);
    else if (split[0][0] == 'A')
        parsing_ambiant(split,scene);
    else if (split[0][0] == 'l')
        parsing_light(split,scene);
    else if (ft_strncmp(split[0],"c",2) == 0)
        parsing_camera(split,scene);
    else if (ft_strncmp(split[0],"pl",2) == 0)
        parsing_plan(split,scene);
    else if (ft_strncmp(split[0],"sp",2) == 0)
        parsing_sphere(split,scene);
    else if (ft_strncmp(split[0],"sq",2) == 0)
        parsing_square(split,scene);
    else if (ft_strncmp(split[0],"tr",2) == 0)
        parsing_triangle(split,scene);
    else if (ft_strncmp(split[0],"cy",2) == 0)
        parsing_cylinder(split,scene);
}

void initial_scene(t_scene *scene)
{
    scene->resolution = NULL;
    scene->ambient = NULL;
    scene->light = NULL;
    scene->camera = NULL;
    scene->objects = NULL;
}
t_scene *parsing(int fd)
{
    t_scene *scene;
    scene = malloc(sizeof(t_scene));

    initial_scene(scene);
    char *line;
    while(get_next_line(fd,&line) > 0)
		{
            parsing_line(line,scene);
			free(line);
		}
    parsing_line(line,scene);
    free(line);
    return scene;
}