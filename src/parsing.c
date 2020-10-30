/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:24:02 by zjamali           #+#    #+#             */
/*   Updated: 2020/10/30 11:44:07 by zjamali          ###   ########.fr       */
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
        new->prev = *alst;
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
    camera->prev = NULL; 

    camera->fov = ft_atoi(cam[3]);
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

    ft_lstadd_back_light(&scene->light,light);
}

void parsing_plan(char **pl,t_scene *scene)
{
    t_obj_properties obj;
    t_plane *plane;
    t_object *new_object;

    plane = malloc(sizeof(t_plane));
    obj.origin  = ft_split(pl[1],',');
    plane->coord.x = ft_atof(obj.origin[0]);
    plane->coord.y = ft_atof(obj.origin[1]);
    plane->coord.z = ft_atof(obj.origin[2]);
    obj.normal  = ft_split(pl[2],',');
    plane->orientation.x = ft_atof(obj.normal[0]);
    plane->orientation.y = ft_atof(obj.normal[1]);
    plane->orientation.z = ft_atof(obj.normal[2]); 
    obj.color  = ft_split(pl[3],',');
    plane->color.x = ft_atoi(obj.color[0]);
    plane->color.y = ft_atoi(obj.color[1]);
    plane->color.z = ft_atoi(obj.color[2]);
    new_object = malloc(sizeof(t_object));
    new_object->object_type = 'p';
    new_object->object = plane;
    new_object->origin = plane->coord;
    new_object->orientation = plane->orientation;
    new_object->color = &plane->color;
    new_object->next = NULL;
    ft_lstadd_back(&scene->objects,new_object);
}

void parsing_sphere(char **sph,t_scene *scene)
{
    t_obj_properties obj;
    t_sphere *sphere;
    t_object *new_object;

    sphere = malloc(sizeof(t_sphere));
    obj.origin  = ft_split(sph[1],',');
    sphere->origin.x = ft_atof(obj.origin[0]);
    sphere->origin.y = ft_atof(obj.origin[1]);
    sphere->origin.z = ft_atof(obj.origin[2]);
    sphere->radius  = ft_atof(sph[2]) / 2;
    obj.color  = ft_split(sph[3],',');
    sphere->color.x = ft_atoi(obj.color[0]);
    sphere->color.y = ft_atoi(obj.color[1]);
    sphere->color.z = ft_atoi(obj.color[2]);
    new_object = malloc(sizeof(t_object));
    new_object->object_type = 's';
    new_object->object = sphere;
    new_object->origin = sphere->origin;
    new_object->color = &sphere->color;
    new_object->radius = sphere->radius;
    new_object->next = NULL;
    ft_lstadd_back(&scene->objects,new_object);
}

void parsing_square(char **sqr,t_scene *scene)
{
    t_obj_properties obj;
    t_square *square;
    t_object *new_object;

    square = malloc(sizeof(t_square));
    obj.origin  = ft_split(sqr[1],',');
    square->center.x = ft_atof(obj.origin[0]);
    square->center.y = ft_atof(obj.origin[1]);
    square->center.z = ft_atof(obj.origin[2]);
    obj.normal  = ft_split(sqr[2],',');
    square->normal.x = ft_atof(obj.normal[0]);
    square->normal.y = ft_atof(obj.normal[1]);
    square->normal.z = ft_atof(obj.normal[2]);
    square->edge_size  = ft_atof(sqr[3]);
    obj.color  = ft_split(sqr[4],',');
    square->color.x = ft_atoi(obj.color[0]);
    square->color.y = ft_atoi(obj.color[1]);
    square->color.z = ft_atoi(obj.color[2]);   
    new_object = malloc(sizeof(t_object));
    new_object->object_type = 'q';
    new_object->object = square;
    new_object->origin = square->center;
    new_object->orientation = square->normal;
    new_object->size = square->edge_size;
    new_object->color = &square->color;
    new_object->next = NULL;
    ft_lstadd_back(&scene->objects,new_object);
}

void parsing_triangle(char **tr,t_scene *scene)
{
    t_obj_properties obj;
    t_triangle *triangle;
    t_object *new_object;

    triangle = malloc(sizeof(t_triangle));
    obj.cord1  = ft_split(tr[1],',');
    triangle->vectors[0].x = ft_atof(obj.cord1[0]);
    triangle->vectors[0].y = ft_atof(obj.cord1[1]);
    triangle->vectors[0].z = ft_atof(obj.cord1[2]);
    obj.cord2  = ft_split(tr[2],',');
    triangle->vectors[1].x = ft_atof(obj.cord2[0]);
    triangle->vectors[1].y = ft_atof(obj.cord2[1]);
    triangle->vectors[1].z = ft_atof(obj.cord2[2]);
    obj.cord3  = ft_split(tr[3],',');
    triangle->vectors[2].x = ft_atof(obj.cord3[0]);
    triangle->vectors[2].y = ft_atof(obj.cord3[1]);
    triangle->vectors[2].z = ft_atof(obj.cord3[2]);
    obj.color  = ft_split(tr[4],',');
    triangle->color.x = ft_atoi(obj.color[0]);
    triangle->color.y = ft_atoi(obj.color[1]);
    triangle->color.z = ft_atoi(obj.color[2]);
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
    t_obj_properties obj;
    t_cylinder *cylinder;
    t_object *new_object;
    
    cylinder = malloc(sizeof(t_cylinder));
    obj.origin  = ft_split(cy[1],',');
    cylinder->coord.x = ft_atof(obj.origin[0]);
    cylinder->coord.y = ft_atof(obj.origin[1]);
    cylinder->coord.z = ft_atof(obj.origin[2]);
    obj.normal  = ft_split(cy[2],',');
    cylinder->normal.x = ft_atof(obj.normal[0]);
    cylinder->normal.y = ft_atof(obj.normal[1]);
    cylinder->normal.z = ft_atof(obj.normal[2]);
    obj.color  = ft_split(cy[5],',');
    cylinder->color.x = ft_atoi(obj.color[0]);
    cylinder->color.y = ft_atoi(obj.color[1]);
    cylinder->color.z = ft_atoi(obj.color[2]);
    cylinder->diameter = ft_atof(cy[3]);
    cylinder->height = ft_atof(cy[4]);
    
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
}

void parsing_line(char *line,t_scene *scene)
{
    char **split;
    split = ft_split(line, ' '); /// need adding /t ... to spliting line  
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