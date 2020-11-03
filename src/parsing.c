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
        new->prev = temp;
        //new->prev = *alst;
	}
	else
		*alst = new;
}
void parsing_resolution(char **resol,t_scene *scene)
{
    t_resolution *resolution;
    resolution = malloc(sizeof(t_resolution));
    if (scene->resolution != NULL)
        ft_print_error("You can't specify resolution twice.");
    if (resol[1] == NULL || resol[2] == NULL)
        ft_print_error("you have to specify the width and height.");
    resolution->width = ft_atoi(resol[1]);
    resolution->height = ft_atoi(resol[2]);
    scene->resolution = resolution;
}

void parsing_ambiant(char **amb,t_scene *scene)
{
    t_ambient *ambient;
    char **color;
    ambient = malloc(sizeof(t_ambient));
    if (scene->ambient != NULL)
        ft_print_error("You can't specify ambient twice.");
    if (amb[1] == NULL || amb[2] == NULL)
        ft_print_error("you have to specify the intensity and color.");
    ambient->intensity = ft_atof(amb[1]);
    color  = ft_split(amb[2],',');
    ambient->color.x = ft_atoi(color[0]);
    ambient->color.y = ft_atoi(color[1]);
    ambient->color.z = ft_atoi(color[2]);

    scene->ambient = ambient;
}
t_vector ft_parse_normal(char **norm)
{
    t_vector normal;
    normal.x = ft_atof(norm[0]);
    normal.y = ft_atof(norm[1]);
    normal.z = ft_atof(norm[2]);
    normal = normalize(&normal);
    return normal;
}

int ft_check_normal(char **norm)
{
    t_vector normal;
    if (norm[0] == NULL || norm[1] == NULL || norm[2] == NULL)
        return (1);
    else
    {
        normal = ft_parse_normal(norm);
    if (normal.x < -1 || normal.x > 1 || normal.y < -1 || normal.y > 1 || 
        normal.z < -1 || normal.z > 1)
        return (1);
    }
    return (0);
}
t_vector ft_parse_color(char **colors)
{
    t_vector color;

    color.x = ft_atoi(colors[0]);
    color.y = ft_atoi(colors[1]);
    color.z = ft_atoi(colors[2]);
    return color;
}
int ft_check_color(char **color)
{
    t_vector colors;

    if (color[0] == NULL || color[1] == NULL || color[2] == NULL)
        return (1);
    else
    {
        colors = ft_parse_color(color);
        if (colors.x < 0 || colors.x > 255 || colors.y < 0 || colors.y > 255 || 
        colors.z < 0 || colors.z > 255)
            return (1);
    }
    return (0);
}
int ft_check_coords(char **coord)
{
    if (coord[0] == NULL || coord[1] == NULL || coord[2] == NULL)
        return (1);
    return 0;
}
t_vector ft_parse_coord(char **coord)
{
    t_vector coords;

    coords.x = ft_atof(coord[0]);
    coords.y = ft_atof(coord[1]);
    coords.z = ft_atof(coord[2]);
    return coords;
}
void parsing_camera(char **cam,t_scene *scene)
{
    char **origin;
    char **normal;
    int field_view;
    t_camera *camera;

    //if (cam[1] == NULL || cam[2] == NULL || cam[3] == NULL)
    //    ft_print_error("you have to specify the camera look from,orientation and field of view.");
    origin  = ft_split(cam[1],',');
    normal  = ft_split(cam[2],',');
    field_view = ft_atoi(cam[3]);
    //if (ft_check_coords(origin))
    //    ft_print_error("camera coordination x,y,z");
    //if (ft_check_normal(normal))
    //    ft_print_error("camera orientation x,y,z must be betwenn -1 and 1");
    //if (field_view > 180 || field_view < 0)
    //    ft_print_error("camera is field of view must be between 0 and 180");

    camera = malloc(sizeof(t_camera));
    camera->lookfrom = ft_parse_coord(origin);
    camera->orientaion = ft_parse_normal(normal);
    camera->fov = field_view;
    camera->next = NULL;
    camera->prev = NULL;
    ft_lstadd_back_camera(&scene->camera,camera);
    
}

void parsing_light(char ** li,t_scene *scene)
{
    char **origin;
    char **color;
    int intensity;
    t_light *light;

    //if (light[1] == NULL || light[2] == NULL || light[3] == NULL)
    //    ft_print_error("you have to specify the light coordinations, intensity and color.");
    origin  = ft_split(li[1],',');
    intensity = ft_atof(li[2]);
    color  = ft_split(li[3],',');

    //if (ft_check_coords(origin))
    //    ft_print_error("light coordinations.");
    //if (intensity > 1 || intensity < 0)
    //    ft_print_error("light intensity must be in range [0,1]");
    //if (ft_check_color(color))
    //    ft_print_error("light color red,green,blue must be between 0 and 255");
    
    light = malloc(sizeof(t_light));
    light->origin = ft_parse_coord(origin);
    light->color = ft_parse_color(color);
    light->intensity = intensity;
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
    split = ft_split(line, ' ');
    if (!split)
        ft_print_error("empty line"); // need 
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

void ft_check_element(char *line)
{
    char **split;
    split = ft_split(line, ' ');
    if (split[0][0] != 'R' && split[0][0] != 'A' && split[0][0] != 'l'
    && ft_strncmp(split[0],"c",2) && ft_strncmp(split[0],"pl",2) && 
    ft_strncmp(split[0],"sp",2) && ft_strncmp(split[0],"sq",2) &&
    ft_strncmp(split[0],"tr",2) && ft_strncmp(split[0],"cy",2) )
    {
        ft_print_error("unknown element in the scene.");
    }
}
void ft_check_line(char *line)
{
    int i;

    if (!line[0])
        ft_print_error("empty line");
    ft_check_element(line);
    i = 2;
    while (line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '\t' && line [i] != ',' && 
        line[i] != '.' && (line[i] < '0' && line[i] > '9'))
            ft_print_error("undifined symbole in the scene file");
        i++;
    }
}
void ft_check_scene(t_scene *scene);
t_scene *parsing(int fd)
{
    t_scene *scene;
    scene = malloc(sizeof(t_scene));

    initial_scene(scene);
    char *line;
    while(get_next_line(fd,&line) > 0)
	{
        ft_check_line(line);
        parsing_line(line,scene);
		free(line);
	}
    parsing_line(line,scene);
    ft_check_line(line);
    ft_check_scene(scene);
    free(line);
    return scene;
}

void  ft_check_scene(t_scene *scene)
{
    int height;
    int width;

    width = 1080;
    height = 720;
    //mlx_get_screen_size(scene->mlx_ptr,&width,&height);
    if (scene->camera == NULL)
        ft_print_error("No camera in the scene,you need at least one camera in the scene.");
    else if (scene->resolution == NULL)
        ft_print_error("you have to specify the resolution.");
    else if (scene->resolution->height <= 0 || scene->resolution->width <= 0)
        ft_print_error("you have to specify positive width and height");
    else if (scene->resolution->height > height)
        scene->resolution->height = height;
    else if (scene->resolution->width > width)
        scene->resolution->width = width;
}
