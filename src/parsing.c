/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:24:02 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/13 13:29:43 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object    *ft_lstlast(t_object *lst)
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

void    ft_lstadd_back(t_object **alst, t_object *new)
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

void    ft_lstadd_back_light(t_light **alst, t_light *new)
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

t_camera    *ft_lstlast_camera(t_camera *lst)
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

void    ft_lstadd_back_camera(t_camera **alst, t_camera *new)
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

void    parsing_resolution(char **resol,t_scene *scene)
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

void    parsing_ambiant(char **amb, t_scene *scene)
{
    char **color;

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

t_vector    ft_parse_normal(char **norm)
{
    t_vector normal;

    normal.x = ft_atof(norm[0]);
    normal.y = ft_atof(norm[1]);
    normal.z = ft_atof(norm[2]);
    normal = normalize(normal);
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
t_vector    ft_parse_color(char **colors)
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
t_vector    ft_parse_coord(char **coord)
{
    t_vector coords;

    coords.x = ft_atof(coord[0]);
    coords.y = ft_atof(coord[1]);
    coords.z = ft_atof(coord[2]);
    return coords;
}

void  ft_element_can_transforme(t_scene *scene,char wich_element,void *the_element)
{
    if (scene->element_to_transform == NULL)
        scene->element_to_transform = malloc(sizeof(t_element_to_transform));
    
    scene->element_to_transform->wich_element = wich_element;
    scene->element_to_transform->element = the_element;
}

void    parsing_camera(char **cam,t_scene *scene)
{
    char **origin;
    char **orient;
    int fiel_view;
    t_camera *camera;

    if (cam[3] == NULL)
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
    ft_element_can_transforme(scene,'c',camera);
}

void    parsing_light(char ** light_line,t_scene *scene)
{
    char **origin;
    char **color;
    double intensity;
    t_light *light;

    if (light_line[3] == NULL)
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
    ft_element_can_transforme(scene,'l',light);
}
void    ft_check_plane(t_obj_properties obj)
{
    if(ft_check_coords(obj.origin))
        ft_print_error("coordinates of the plan  x,y,z");
    if (ft_check_normal(obj.normal))
        ft_print_error(" normalized orientation vector of plan it's axis in range [0,1]");
    if(ft_check_color(obj.color))
        ft_print_error("plan color in range [0,255]");
}
void    parsing_plan(char **pl,t_scene *scene)
{
    t_obj_properties obj;
    t_plane *plane;
    t_object *new_object;

    if (pl[3] == NULL) /// some of properties missing
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
    ft_element_can_transforme(scene,'p',new_object);
}
void    ft_check_sphere(t_obj_properties obj)
{
    if (ft_check_coords(obj.origin))
        ft_print_error("coordinates of the sphere  x,y,z");
    if (ft_check_color(obj.color))
        ft_print_error("sphere color in range [0,255]");
    if (obj.diameter < 0)
        ft_print_error("shpere diameter must be positive");
}

void    parsing_sphere(char **sph,t_scene *scene)
{
    t_obj_properties obj;
    t_sphere *sphere;
    t_object *new_object;

    if (sph[3] == NULL)
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
    ft_element_can_transforme(scene,'s',new_object);
}
void    ft_check_square(t_obj_properties obj)
{
    if (ft_check_coords(obj.origin))
        ft_print_error("coordinates of the squqre  x,y,z");
    if (ft_check_color(obj.color))
        ft_print_error("square color in range [0,255]");
    if (obj.size < 0)
        ft_print_error("shpere edge size must be positive");
     if (ft_check_normal(obj.normal))
        ft_print_error(" normalized orientation vector of square it's axis in range [0,1]");  
}

void    parsing_square(char **sqr,t_scene *scene)
{
    t_obj_properties obj;
    t_square *square;
    t_object *new_object;

    if (sqr[4] == NULL)
        ft_print_error("you have to specify the square center coordination point,orientation,edge size and color.");
    obj.origin  = ft_split(sqr[1],',');
    obj.normal  = ft_split(sqr[2],',');
    obj.color  = ft_split(sqr[4],',');
    obj.size = ft_atof(sqr[3]);
    ft_check_square(obj);

    square = malloc(sizeof(t_square));
    square->edge_size  = obj.size;
    square->center = ft_parse_coord(obj.origin);
    square->normal = ft_parse_normal(obj.normal);
    square->color = ft_parse_color(obj.color); 

    new_object = malloc(sizeof(t_object));
    new_object->object_type = 'q';
    new_object->object = square;
    new_object->origin = square->center;
    new_object->orientation = square->normal;
    new_object->size = square->edge_size;
    new_object->color = &square->color;
    new_object->next = NULL;
    ft_lstadd_back(&scene->objects,new_object);
    ft_element_can_transforme(scene,'q',new_object);
}
void    ft_check_triangle(t_obj_properties obj)
{
    if (ft_check_coords(obj.cord1))
            ft_print_error("first coordinates of the traingle  x,y,z");
    if (ft_check_coords(obj.cord2))
            ft_print_error("second coordinates of the traingle  x,y,z");
    if (ft_check_coords(obj.cord2))
            ft_print_error("third coordinates of the traingle  x,y,z");
    if (ft_check_color(obj.color))
            ft_print_error("trangle color in range [0,255]"); 
}
void    parsing_triangle(char **tr,t_scene *scene)
{
    t_obj_properties obj;
    t_triangle *triangle;
    t_object *new_object;

    if (tr[4] == NULL)
        ft_print_error("you have to specify three trangle points and its color.");
    obj.cord1  = ft_split(tr[1],',');
    obj.cord2  = ft_split(tr[2],',');
    obj.cord3  = ft_split(tr[3],',');
    obj.color  = ft_split(tr[4],',');

    ft_check_triangle(obj);

    triangle = malloc(sizeof(t_triangle));
    triangle->vectors[0] = ft_parse_coord(obj.cord1);
    triangle->vectors[1] = ft_parse_coord(obj.cord2);
    triangle->vectors[2] = ft_parse_coord(obj.cord3);
    triangle->color = ft_parse_color(obj.color);

    new_object = malloc(sizeof(t_object));
    new_object->object = triangle;
	new_object->color = &triangle->color;
	new_object->object_type = 't';
	new_object->v3[0] = triangle->vectors[0];
	new_object->v3[1] = triangle->vectors[1];
	new_object->v3[2] = triangle->vectors[2];
    new_object->next = NULL;
    ft_lstadd_back(&scene->objects,new_object);
    ft_element_can_transforme(scene,'t',new_object);
}
void    ft_check_cylinder(t_obj_properties obj)
{
    if(ft_check_coords(obj.origin))
        ft_print_error("coordinates of the cylinder  x,y,z");
    if (ft_check_normal(obj.normal))
        ft_print_error(" normalized orientation vector of cylinder it's axis in range [0,1]");
    if(ft_check_color(obj.color))
        ft_print_error("cylinder color in range [0,255]");
    if (obj.size < 0)
        ft_print_error("cyliner height size must be positive");
    if (obj.diameter < 0)
        ft_print_error("cylinder diameter must be positive");
}
void    parsing_cylinder(char **cy,t_scene *scene)
{
    t_obj_properties obj;
    t_cylinder *cylinder;
    t_object *new_object;

    if (cy[5] == NULL)
        ft_print_error("you have to specify cylinder coordination points ,orientation,diametre,size and color.");
    obj.origin  = ft_split(cy[1],',');
    obj.normal  = ft_split(cy[2],',');
    obj.color  = ft_split(cy[5],',');
    obj.diameter = ft_atof(cy[3]);
    obj.size = ft_atof(cy[4]);

    ft_check_cylinder(obj);
    cylinder = malloc(sizeof(t_cylinder));

    cylinder->coord = ft_parse_coord(obj.origin);
    cylinder->normal = ft_parse_normal(obj.normal);
    cylinder->color = ft_parse_color(obj.color);
    cylinder->diameter = obj.diameter;
    cylinder->height = obj.size;
    
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
    ft_element_can_transforme(scene,'y',new_object);
}
void ft_translate_sphere(t_scene *scene)
{
    t_object *obj;
    t_sphere *sp;
    
    obj = scene->element_to_transform->element;
    sp = obj->object;
    sp->origin = vectorsadd(sp->origin,scene->element_to_transform->transform.trans);
    obj->origin = vectorsadd(obj->origin,scene->element_to_transform->transform.trans);

}
void ft_translate_plane(t_scene *scene)
{
    t_object *obj;
    t_plane *plan;
    
    obj = scene->element_to_transform->element;
    plan = obj->object;
    plan->coord = vectorsadd(plan->coord,scene->element_to_transform->transform.trans);
    obj->origin = vectorsadd(obj->origin,scene->element_to_transform->transform.trans);
    
    
}

void ft_translate_square(t_scene *scene)
{
    t_object *obj;
    t_square *square;
    
    obj = scene->element_to_transform->element;
    square = obj->object;
    square->center = vectorsadd(square->center,scene->element_to_transform->transform.trans);
    obj->origin = vectorsadd(obj->origin,scene->element_to_transform->transform.trans);

}
void ft_translate_traiangle(t_scene *scene)
{
    t_object *obj;
    t_triangle *trn;
    obj = scene->element_to_transform->element;
    trn = obj->object;
    
    obj->v3[0] = vectorsadd(obj->v3[0],scene->element_to_transform->transform.trans);
    obj->v3[1] = vectorsadd(obj->v3[1],scene->element_to_transform->transform.trans);
    obj->v3[2] = vectorsadd(obj->v3[2],scene->element_to_transform->transform.trans);
    
    trn->vectors[0] = vectorsadd(trn->vectors[0],scene->element_to_transform->transform.trans);
    trn->vectors[1] = vectorsadd(trn->vectors[1],scene->element_to_transform->transform.trans);
    trn->vectors[2] = vectorsadd(trn->vectors[2],scene->element_to_transform->transform.trans);
    
}
void ft_translate_cylinder(t_scene *scene)
{
    t_object *obj;
    t_cylinder *cy;

    obj = scene->element_to_transform->element;
    cy = obj->object;
    obj->origin = vectorsadd(obj->origin,scene->element_to_transform->transform.trans);
    cy->coord = vectorsadd(cy->coord,scene->element_to_transform->transform.trans);
    
}
void ft_make_translation(t_scene *scene)
{
    write(1,"translation\n",ft_strlen("translation\n"));
    if (scene->element_to_transform->wich_element == 'l')
    {
        t_light *light;
        light = scene->element_to_transform->element;
        light->origin = vectorsadd(light->origin,scene->element_to_transform->transform.trans);
    }
    else if (scene->element_to_transform->wich_element == 'c')
    {
        t_camera *cam;
        cam = scene->element_to_transform->element;
        cam->lookfrom = vectorsadd(cam->lookfrom,scene->element_to_transform->transform.trans);
    }
    else if (scene->element_to_transform->wich_element == 's')
        ft_translate_sphere(scene);
    else if (scene->element_to_transform->wich_element == 'p')
        ft_translate_plane(scene);
    else if (scene->element_to_transform->wich_element == 'q')
        ft_translate_square(scene);
    else if (scene->element_to_transform->wich_element == 't')
        ft_translate_traiangle(scene);
    else if (scene->element_to_transform->wich_element == 'y')
        ft_translate_cylinder(scene);
    scene->element_to_transform->transform.trans = bzero_vector(scene->element_to_transform->transform.trans);
}

void parse_translation(char **line,t_scene *scene)
{
    char **tran;
    if (line[1] == NULL)
        ft_print_error("you have to specify the transation coordination");
    else
    {
        tran = ft_split(line[1],',');
        if (scene->element_to_transform != NULL)
        {
            scene->element_to_transform->transform.trans = ft_parse_coord(tran);
            ft_make_translation(scene);
        }
    }
}
t_vector *ft_calcule_rotaion_x_axis(double angle,t_vector *orientation)
{
    t_vector *new_orientaion;
    
    new_orientaion = malloc(sizeof(t_vector));
    
    angle = angle * PI /180;
    new_orientaion->y = orientation->y *cos(angle) - orientation->z * sin(angle);
    new_orientaion->z = orientation->y *sin(angle) +  orientation->z * cos(angle);
    new_orientaion->x = orientation->x;
    return new_orientaion;
}
t_vector *ft_calcule_rotaion_y_axis(double angle,t_vector *orientation)
{
    t_vector *new_orientaion;
    
    new_orientaion = malloc(sizeof(t_vector));
    
    angle = angle * PI /180;

    new_orientaion->z = orientation->z * cos(angle) - orientation->x * sin(angle);
    new_orientaion->x = orientation->z * sin(angle) + orientation->x * cos(angle);
    new_orientaion->y = orientation->y;
    return new_orientaion;
}
t_vector *ft_calcule_rotaion_z_axis(double angle,t_vector *orientation)
{
    t_vector *new_orientaion;

    new_orientaion = malloc(sizeof(t_vector));
    
    angle = angle * PI /180;
    new_orientaion->x =  orientation->x * cos(angle) -  orientation->y *  sin(angle);
    new_orientaion->y =  orientation->x * sin(angle) +   orientation->y * cos(angle);
    new_orientaion->z = orientation->z;
    return new_orientaion;
}
//void ft_rotate_cylinder(t_scene *scene)
//{
//    
//}
t_vector ft_calcule_rotaion(t_vector orientation,t_vector rotaion)
{
    t_vector *new_orientation;
    new_orientation = malloc(sizeof(t_vector));
    
    new_orientation->x = orientation.x;
    new_orientation->y = orientation.y;
    new_orientation->z = orientation.z;
    
    new_orientation =  ft_calcule_rotaion_x_axis(rotaion.x,new_orientation);
    new_orientation =  ft_calcule_rotaion_y_axis(rotaion.y,new_orientation);
    new_orientation =  ft_calcule_rotaion_z_axis(rotaion.z,new_orientation);
    
    *new_orientation = normalize(*new_orientation);
    return *new_orientation;
}
void ft_make_rotation(t_scene *scene)
{
     write(1,"rotation\n",ft_strlen("rotation\n"));
    if (scene->element_to_transform->wich_element == 'c')
    {
        t_camera *cam;
        cam = scene->element_to_transform->element;
        cam->orientaion = ft_calcule_rotaion(cam->orientaion,scene->element_to_transform->transform.rot);
    }
    else if (scene->element_to_transform->wich_element == 'y')
    {
        t_cylinder *cy;
        t_object *obj;
        obj = scene->element_to_transform->element;
        cy = obj->object;
        obj->orientation = ft_calcule_rotaion(obj->orientation,scene->element_to_transform->transform.rot);
        cy->normal = ft_calcule_rotaion(cy->normal,scene->element_to_transform->transform.rot);
    }
    else if (scene->element_to_transform->wich_element == 'p')
    {
        t_plane *pl;
        t_object *obj;
        obj = scene->element_to_transform->element;
        pl = obj->object;
        obj->orientation = ft_calcule_rotaion(obj->orientation,scene->element_to_transform->transform.rot);
        pl->orientation = ft_calcule_rotaion(pl->orientation,scene->element_to_transform->transform.rot);
    }
    else if (scene->element_to_transform->wich_element == 'q')
    {
        t_square *sq;
        t_object *obj;
        obj = scene->element_to_transform->element;
        sq = obj->object;
        obj->orientation = ft_calcule_rotaion(obj->orientation,scene->element_to_transform->transform.rot);
        sq->normal = ft_calcule_rotaion(sq->normal,scene->element_to_transform->transform.rot);
    }
    scene->element_to_transform->transform.rot = bzero_vector(scene->element_to_transform->transform.rot);
}

void parse_rotation(char **line,t_scene *scene)
{
    
    char **rot;
    if (line[1] == NULL)
        ft_print_error("you have to specify the rotation angles");
    else
    {
        rot = ft_split(line[1],',');
        if (scene->element_to_transform != NULL)
        {
            scene->element_to_transform->transform.rot = ft_parse_coord(rot);
            ft_make_rotation(scene);
        }
    }
}

void    parsing_line(char *line,t_scene *scene)
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
    else if (ft_strncmp(split[0],"tr",3) == 0)
        parsing_triangle(split,scene);
    else if (ft_strncmp(split[0],"cy",2) == 0)
        parsing_cylinder(split,scene);
    else if (ft_strncmp(split[0],"tra",3) == 0)
        parse_translation(split,scene);
    else if (ft_strncmp(split[0],"rot",3) == 0)
        parse_rotation(split,scene);
}

void    ft_check_element(char *line)
{
    char **split;
    split = ft_split(line, ' ');
    if (split[0][0] != 'R' && split[0][0] != 'A' && split[0][0] != 'l'
        && ft_strncmp(split[0],"c",2) && ft_strncmp(split[0],"pl",2) && 
        ft_strncmp(split[0],"sp",2) && ft_strncmp(split[0],"sq",2) &&
        ft_strncmp(split[0],"tr",2) && ft_strncmp(split[0],"cy",2) &&
        ft_strncmp(split[0],"rot",3) && ft_strncmp(split[0],"tra",3))
            ft_print_error("unknown element in the scene.");
}

int    ft_check_line(char *line)
{
    int i;
    i =  0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == '\0')
        return 0;
    ft_check_element(line);

    while (line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '\t' && line [i] != ',' && 
        line[i] != '.' && (line[i] < '0' && line[i] > '9'))
            ft_print_error("undifined symbole in the scene file");
        i++;
    }
    return (1);
}

void    ft_check_scene(t_scene *scene)
{
    int height;
    int width;
    /// imac size 5120 x 2880
    width = 5120;
    height = 2880;
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
            if(ft_check_line(line))
                parsing_line(line,scene);
		    free(line);
        }
	}
    if (line[0])  /// skip empty line
        {
            if (ft_check_line(line))
                parsing_line(line,scene);
		    free(line);
        }
    ft_check_scene(scene);
    return scene;
}