
#include "minirt.h"


t_vector	ft_calcule_normal(t_scene *scene, t_object *object, t_vector p, double t)
{
	t_vector n;
	t_noraml_variables nrml;

	if (object->object_type == 's')
		n  = vectorsSub(p,object->origin);
	if (object->object_type == 'p' || object->object_type == 'q')
	{
		n = object->orientation;
		if (vectorsDot(n,scene->ray->direction) > __DBL_EPSILON__) ///
			n = vectorscal(n,-1);
	}
	if (object->object_type == 't')
	{
		nrml.edge1 = vectorsSub(object->v3[1],object->v3[0]); // 1 0 
		nrml.edge2 = vectorsSub(object->v3[2],object->v3[0]); // 2 0
		nrml.h = vecttorscross(nrml.edge1,nrml.edge2);
		n = normalize(nrml.h);
		if (vectorsDot(n,scene->ray->direction) > __DBL_EPSILON__) ///
			n = vectorscal(n,-1);
	}
	if (object->object_type == 'c')
	{
		object->orientation = normalize(object->orientation);
		nrml.oc =  vectorsSub(scene->ray->origin,object->origin);
		nrml.m = vectorsDot(scene->ray->direction,object->orientation) * t 
					+ vectorsDot(nrml.oc,object->orientation);
		//    N = nrm( P-C-V*m )
		nrml.normal = vectorsSub(p,object->origin);
		nrml.line_point = vectorscal(object->orientation,nrml.m);
		n = vectorsSub(nrml.normal,nrml.line_point);
	}
	n = normalize(n);
	return (n);
}

double	ft_get_first_intersection(t_object *temps,t_ray p_ray,t_object *closet_object)
{
	double closet_object1_t;
	double closet_object_t;
	t_object *first_intersection_object;

    closet_object1_t = 0;
    closet_object_t = 1000000000000;
	while (temps != NULL)
		{
			if (temps->object_type == 'c')
					closet_object1_t = 	hit_cylinder(p_ray,temps->object);
			if (temps->object_type == 's')
				closet_object1_t = hit_sphere(p_ray,temps->object);
			else if (temps->object_type == 'p')
				closet_object1_t = hit_plane(p_ray,temps->object);
			else if(temps->object_type == 't')
				closet_object1_t = hit_triangle(p_ray,temps->object);
			else if(temps->object_type == 'q')
				closet_object1_t = hit_square(p_ray,temps->object);
			if (closet_object1_t > 0)
				if (closet_object1_t < closet_object_t)
				{
					first_intersection_object = temps;
					closet_object_t = closet_object1_t;
				}
			temps = temps->next;
		}
		// for doesnt intersect with same object with calcule it shadaw
		if (closet_object == first_intersection_object)
			return (1000000000000);
		return (closet_object_t);
}