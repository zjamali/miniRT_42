/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:05:13 by zjamali           #+#    #+#             */
/*   Updated: 2020/10/30 11:40:39 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# define MINIRT_H
#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <mlx.h>
//#include "/usr/X11/include/mlx.h"
#define max(a,b) ((double)a > (double)b ? (double)a : (double)b)
#define min(a,b) ((double)a > (double)b ? (double)b : (double)a)
#define PI 3.1415926535897932

typedef struct  s_imag {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_imag;

typedef struct s_vector
{
	float x,y,z;
}t_vector;

typedef struct s_sphere
{
	t_vector origin;
	double  radius;
	t_vector color;
}t_sphere;

typedef struct s_plane
{
	t_vector coord;
	t_vector orientation;
	t_vector color;
}t_plane;

typedef struct s_triangle
{
	t_vector vectors[3];
	t_vector color;
}t_triangle;

typedef struct s_disk
{
	t_vector coord;
	t_vector orientation;		
	double radius;
	t_vector color;
}t_disk;

typedef struct s_square
{
	t_vector center;
	t_vector normal;
	double edge_size;
	t_vector color;
}t_square;

typedef struct s_cylinder
{
	t_vector coord;
	t_vector normal;
	double height;
	double diameter;
	t_vector color;
}t_cylinder;



typedef struct s_ray
{
	t_vector origin;
	t_vector direction;
}t_ray;

typedef struct  s_camera
{
	t_vector lookfrom;
	t_vector orientaion;
	double fov;
	struct s_camera *next;
	struct s_camera *prev;
}t_camera;

typedef struct  s_object
{
	void *object;
	t_vector *color;
	t_vector origin;
	t_vector orientation;
	char object_type;
	t_vector v3[3];
	double size;
	double radius;
	double diameter;
	struct s_object *next;
}t_object;

typedef struct s_ambient
{
	double intensity;
	t_vector color;
}t_ambient;

typedef struct s_light
{
	t_vector origin;
	double intensity;
	t_vector color;
	struct s_light *next;
	
}t_light;

typedef struct resolution
{
	int height;
	int width;
}t_resolution;


typedef struct  s_scene
{
	int color_of_pixel;
	int fd;
	t_ray *ray;
	t_object *objects;
	t_camera *camera;
	t_camera *multi_camera;
	t_light *light;
	t_ambient *ambient;
	t_resolution *resolution;
	t_imag *img;

	void *mlx_ptr;
	void *win_ptr;
}t_scene;
/**********          variables        ********************/
typedef struct s_camera_variables
{
	t_vector castRay;
	t_vector up;
	t_vector n;
	t_vector u;
	t_vector c;
	t_vector l;
	t_vector v;
	
	double theta;
	double aspectRatio;
	double viewPlaneHalfWidth;
	double viewPlaneHalfHeight;
	
	double W;
	double H;
	
}t_camera_variables;


typedef struct s_phong_variables
{
	double m;
	t_vector color;
	t_vector color1;
	t_vector l_p;
	t_vector scale_direction_to_p;
	t_vector from_camera_to_p;
	t_vector p;
	t_vector n;
	
	double i_diffuse;
	
	int specular;
	double dot;
	t_vector r;
	t_vector reflection;
	double i_specular;
	int specular_shiness;
	
}t_phong_variables;

typedef struct s_shadow_variables
{
	
	t_vector scale_direction_to_p;
	t_vector p;
	int dark;
	t_vector p_l;
	t_ray p_ray;
	double closet_object_t;
	t_object *temps;
	t_vector scale_direction_to_c;
	t_vector c;
	t_vector p_c;
	double p_length;
	double c_length;
	
}t_shadow_variables;

typedef struct s_normal_variables
{
	double m;
	t_vector edge1;
	t_vector edge2;
	t_vector h;
	t_vector oc;
	t_vector normal;
	t_vector line_point;
}t_noraml_variables;

/******** object variables *******/
typedef struct s_sphere_varibales
{
	t_vector oc;
	double a;
	double b;
	double c;
	double delta;
	double t;
	double t1;
	double t2;
	
}t_sphere_variables;

typedef struct s_plane_variables
{
	double t;
	t_vector x;
	t_vector v;
	t_vector d;
	double dot2;
	double dot1;
	
}t_plane_variables;

typedef struct s_traingle_variables
{
	double epsilon;
	
	t_vector edge1;
	t_vector edge2;
	t_vector h;
	t_vector s;
	t_vector q;
	double a;
	double f;
	double u;
	double v;
	double t;
	
}t_triangle_variables;

typedef struct s_square_variables
{
	double size;
	t_vector e1;
	t_vector e2;
	t_vector scale_direction_to_p;
	t_vector p;
	t_vector u;
	double r;
}t_square_variables;

typedef struct s_cylinder_variables
{
	double t;
	t_vector oc;
	double a;
	double b;
	double c;
	double delta;
	double t1;
	double t2;

	double min;
	double max;
}t_cylinder_variables;

typedef struct s_disk_variables
{
	double t;
	t_vector x;
	t_vector v;
	double dot1;
	double dot2;
	t_vector scale_direction_to_p;
	t_vector p;
	t_vector op;
	double h;
	
}t_disk_variables;


/***************     objects properties *******/

typedef struct s_obj_properties
{
	char **origin;
    char **normal;
	
	char **cord1;
    char **cord2;
    char **cord3;

	
    char **color;
}t_obj_properties;


/***********************  VECTOR.C  ***********************/
t_vector  vectorsadd(t_vector *v1,t_vector *v2);
t_vector vectorscal(t_vector *v ,double s);
t_vector vectordiv(t_vector *v, double d);
t_vector vectorsSub(t_vector *v1, t_vector *v2);
double vectorsDot(t_vector *v1, t_vector *v2);
double lenght(t_vector *v);
t_vector normalize(t_vector *v);
t_vector vectorsproduit(t_vector *v1,t_vector *v2);
t_vector vecttorscross(t_vector *v1,t_vector *v2);


/***********************  CAMERA.C  ***********************/
t_vector ft_camera_ray(t_scene *scene,double x,double y);

/***********************  INTERSECTION.C  ***********************/
double hit_sphere(t_ray ray,t_sphere *s);
double hit_plane(t_ray ray,t_plane *plane);
double hit_triangle(t_ray ray,t_triangle *triangle);
double hit_square(t_ray ray,t_square *s_square);
double hit_cylinder(t_ray ray,t_cylinder *cylinder);
//double hit_disk(t_ray ray,t_disk *disk);
/***********************  LIGHT.C  ***********************/
t_vector ft_specular(t_scene *scene,double t,t_object *object);
t_vector ft_diffuse(t_scene *scene,double t,t_object *object);
t_vector ft_ambient(t_ambient *ambient,t_vector *color);
double  ft_shadow(t_scene *scene,t_object *object,double t);

/***********************  PIXEL_COLOR.C  ***********************/

int ft_color_of_pixel(t_scene *scene);
double rgbconvert(int ir, int ig, int ib);

/***********************  FT_SPLIT.C  ***********************/
char			**ft_split(char const *s, char c);
/***********************  ft_atoi.C  ***********************/
int				ft_atoi(const char *str);
/***********************  ft_atof.C  ***********************/
double	ft_atof(const char *str);

/***********************  PARCING.C  ***********************/
t_scene *parsing(int fd);

/***********************  strncmp.C  ***********************/
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//# endif