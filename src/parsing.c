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
    //t_resolution resolution;
   // resolution = malloc(sizeof(t_resolution));
    if (scene->resolution.height != 0)
        ft_print_error("You can't specify resolution twice.");
    if (resol[1] == NULL || resol[2] == NULL)
        ft_print_error("you have to specify the width and height.");
    scene->resolution.width = ft_atoi(resol[1]);
    scene->resolution.height = ft_atoi(resol[2]);
}

void parsing_ambiant(char **amb,t_scene *scene)
{
    //t_ambient ambient;
    char **color;
    //ambient = malloc(sizeof(t_ambient));
    if (scene->ambient.intensity != -1)
        ft_print_error("You can't specify ambient twice.");
    if (amb[1] == NULL || amb[2] == NULL)
        ft_print_error("you have to specify the intensity and color.");
    scene->ambient.intensity = ft_atof(amb[1]);
    color  = ft_split(amb[2],',');
    scene->ambient.color.x = ft_atoi(color[0]);
    scene->ambient.color.y = ft_atoi(color[1]);
    scene->ambient.color.z = ft_atoi(color[2]);
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
        normal.x = ft_atof(norm[0]);
        normal.y = ft_atof(norm[1]);
        normal.z = ft_atof(norm[2]);
        if (normal.x < -1 || normal.x > 1 || normal.y < -1 || normal.y > 1 || 
            normal.z < -1 || normal.z > 1)
            return (1);
        if (normal.x == 0 && normal.y == 0 && normal.z == 0)
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
    char **orient;
    int fiel_view;
    t_camera *camera;

    if (cam[1] == NULL || cam[2] == NULL || cam[3] == NULL)
        ft_print_error("you have to specify the camera look from,orientation and field of view.");
    origin  = ft_split(cam[1],',');
    orient  = ft_split(cam[2],',');
    fiel_view = ft_atoi(cam[3]);
    if (ft_check_coords(origin))
        ft_print_error("camera lookfrom in coordination x,y,z");
    if (ft_check_normal(orient))
        ft_print_error("camera orientation in x,y,z");
    camera = malloc(sizeof(t_camera));
    camera->lookfrom = ft_parse_coord(origin);
    camera->orientaion = ft_parse_normal(orient);
    camera->next = NULL;  
    camera->prev = NULL;
    camera->fov = fiel_view;
    if (camera->fov > 180 || camera->fov < 0)
        ft_print_error("camera is field of view must be between 0 and 180");
    ft_lstadd_back_camera(&scene->camera,camera);
}

void parsing_light(char ** light_line,t_scene *scene)
{
    char **origin;
    char **color;
    double intensity;
    t_light *light;

    if (light_line[1] == NULL || light_line[2] == NULL || light_line[3] == NULL)
        ft_print_error("you have to specify the light coordination point,brightness and color.");
    origin  = ft_split(light_line[1],',');
    color  = ft_split(light_line[3],',');
    intensity = ft_atof(light_line[2]);
    if (ft_check_coords(origin))
        ft_print_error("light coordination point x,y,z");
    if (ft_check_color(color))
        ft_print_error("light color red,green,blue in range [0,255]");
    if (intensity < 0 || intensity > 1)
        ft_print_error("light britness must be in range [0,1]");
    light = malloc(sizeof(t_light));
    light->origin = ft_parse_coord(origin);
    light->color = ft_parse_color(color);
    light->intensity = intensity;
    light->next = NULL;
    ft_lstadd_back_light(&scene->light,light);
}
void ft_check_plane(t_obj_properties obj)
{
    if(ft_check_coords(obj.origin))
        ft_print_error("coordinates of the plan  x,y,z");
    if (ft_check_normal(obj.normal))
        ft_print_error(" normalized orientation vector of plan it's axis in range [0,1]");
    if(ft_check_color(obj.color))
        ft_print_error("plan color in range [0,255]");
}
void parsing_plan(char **pl,t_scene *scene)
{
    t_obj_properties obj;
    t_plane *plane;
    t_object *new_object;

    if (pl[1] == NULL || pl[2] == NULL || pl[3] == NULL)
        ft_print_error("you have to specify the plan coordination point,orientation and color.");
    obj.origin  = ft_split(pl[1],',');
    obj.normal  = ft_split(pl[2],',');
    obj.color  = ft_split(pl[3],',');

    ft_check_plane(obj);

    plane = malloc(sizeof(t_plane));
    plane->coord = ft_parse_coord(obj.origin);
    plane->orientation = ft_parse_normal(obj.normal);
    plane->color = ft_parse_color(obj.color);
    new_object = malloc(sizeof(t_object));
    new_object->object_type = 'p';
    new_object->object = plane;
    new_object->origin = plane->coord;
    new_object->orientation = plane->orientation;
    new_object->color = &plane->color;
    new_object->next = NULL;
    ft_lstadd_back(&scene->objects,new_object);
}
void ft_check_sphere(t_obj_properties obj)
{
    if (ft_check_coords(obj.origin))
        ft_print_error("coordinates of the sphere  x,y,z");
    if (ft_check_color(obj.color))
        ft_print_error("sphere color in range [0,255]");
    if (obj.diameter < 0)
        ft_print_error("shpere diameter must be positive");
}

void parsing_sphere(char **sph,t_scene *scene)
{
    t_obj_properties obj;
    t_sphere *sphere;
    t_object *new_object;

    if (sph[1] == NULL || sph[2] == NULL || sph[3] == NULL)
        ft_print_error("you have to specify the sphere center coordination point,diameter and color.");
    obj.origin  = ft_split(sph[1],',');
    obj.color  = ft_split(sph[3],',');
    obj.diameter = ft_atof(sph[2]);

    ft_check_sphere(obj);

    sphere = malloc(sizeof(t_sphere));
    sphere->radius  = obj.diameter / 2.0;
    sphere->origin = ft_parse_coord(obj.origin);
    sphere->color = ft_parse_color(obj.color);

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

void ft_check_element(char *line)
{
    char **split;
    split = ft_split(line, ' ');
    if (split[0][0] != 'R' && split[0][0] != 'A' && split[0][0] != 'l'
        && ft_strncmp(split[0],"c",2) && ft_strncmp(split[0],"pl",2) && 
        ft_strncmp(split[0],"sp",2) && ft_strncmp(split[0],"sq",2) &&
        ft_strncmp(split[0],"tr",2) && ft_strncmp(split[0],"cy",2) )
            ft_print_error("unknown element in the scene.");
}
void ft_check_line(char *line)
{
    int i;

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

void  ft_check_scene(t_scene *scene)
{
    int height;
    int width;

    width = 1080;
    height = 720;
    //mlx_get_screen_size(scene->mlx_ptr,&width,&height);
    if (scene->camera == NULL)
        ft_print_error("No camera in the scene,you need at least one camera in the scene.");
    if (scene->resolution.height == 0 && scene->resolution.width == 0)
        ft_print_error("you have to specify the resolution.");
    if (scene->resolution.height > height)
        scene->resolution.height = height;
    if (scene->resolution.width > width)
        scene->resolution.width = width;
}

t_scene *parsing(int fd,t_scene *scene)
{
    char *line;
    while(get_next_line(fd,&line) > 0)
	{
        if (line[0])  /// skip empty line
        {
            ft_check_line(line);
            parsing_line(line,scene);
		    free(line);
        }
	}
    ft_check_scene(scene);
    return scene;
}