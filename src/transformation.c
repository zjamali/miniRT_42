
#include "minirt.h"

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
    scene->element_to_transform->transform.rot = bzero_vector();
}
