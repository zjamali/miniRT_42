/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:50:50 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/18 14:41:37 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

typedef struct		s_camera_variables
{
	t_vector		cast_ray;
	t_vector		up;
	t_vector		n;
	t_vector		u;
	t_vector		c;
	t_vector		l;
	t_vector		v;
	double			theta;
	double			aspect_ratio;
	double			view_plane_half_width;
	double			view_plane_half_height;
	double			w;
	double			h;
}					t_camera_variables;

typedef struct		s_phong_variables
{
	double			m;
	t_vector		color;
	t_vector		color1;
	t_vector		l_p;
	t_vector		scale_direction_to_p;
	t_vector		from_camera_to_p;
	t_vector		p;
	t_vector		n;
	double			i_diffuse;
	int				specular;
	double			dot;
	t_vector		r;
	t_vector		reflection;
	double			i_specular;
	int				specular_shiness;

}					t_phong_variables;

typedef struct		s_shadow_variables
{
	t_vector		scale_direction_to_p;
	t_vector		p;
	int				dark;

	double			shadaw;

	t_vector		light_to_p;

	t_ray			light_ray;
	double			closet_object_t;

	t_vector		light_to_c;
	t_object		*temps;

	double			light_to_c_lenght;
	double			light_to_p_lenght;
}					t_shadow_variables;

typedef struct		s_normal_variables
{
	double			m;
	t_vector		edge1;
	t_vector		edge2;
	t_vector		h;
	t_vector		oc;
	t_vector		normal;
	t_vector		line_point;
}					t_noraml_variables;

typedef struct		s_sphere_varibales
{
	t_vector		oc;
	double			a;
	double			b;
	double			c;
	double			delta;
	double			t;
	double			t1;
	double			t2;
}					t_sphere_variables;

typedef struct		s_plane_variables
{
	double			t;
	t_vector		x;
	t_vector		v;
	t_vector		d;
	double			dot2;
	double			dot1;

}					t_plane_variables;

typedef struct		s_traingle_variables
{
	double			epsilon;
	t_vector		edge1;
	t_vector		edge2;
	t_vector		h;
	t_vector		s;
	t_vector		q;
	double			a;
	double			f;
	double			u;
	double			v;
	double			t;
}					t_triangle_variables;

typedef struct		s_square_variables
{
	double			size;
	t_vector		e1;
	t_vector		e2;
	t_vector		scale_direction_to_p;
	t_vector		p;
	t_vector		u;
	double			r;
}					t_square_variables;

typedef struct		s_cylinder_variables
{
	double			t;
	t_vector		oc;
	double			a;
	double			b;
	double			c;
	double			delta;
	double			t1;
	double			t2;
	double			min;
	double			max;
}					t_cylinder_variables;

typedef struct		s_pixel_color
{
	t_vector		colors;
	t_vector		i_specular;
	t_vector		i_diffuse;
	t_vector		i_ambient;
	double			shadow;

	t_object		*closet_object;
	t_object		*temp;
	double			pixel_color;
	double			closet_object_t;
	double			closet_object1_t;
}					t_pixel_color;

t_vector			ft_calcule_normal(t_scene *scene, t_object *object,
												t_vector p, double t);
double				ft_get_first_intersection(t_object *temps, t_ray p_ray,
												t_object *closet_object);
double				hit_sphere(t_ray ray, t_sphere *s);
double				hit_plane(t_ray ray, t_plane *plane);
double				hit_triangle(t_ray ray, t_triangle *triangle);
double				hit_square(t_ray ray, t_square *s_square);
double				hit_cylinder(t_ray ray, t_cylinder *cylinder);

#endif
