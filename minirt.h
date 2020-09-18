/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:05:13 by zjamali           #+#    #+#             */
/*   Updated: 2020/03/14 17:22:05 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIRT_H
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
	t_object *objects;
	t_camera *camera;
	t_light *light;
	t_ambient *ambient;
	t_resolution *resolution;
}t_scene;
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
t_vector ft_camera(t_camera *camera,double H,double W,double x,double y);


/***********************  INTERSECTION.C  ***********************/
double hit_sphere(t_ray ray,t_sphere *s);
double hit_plane(t_ray ray,t_plane *plane);
double hit_triangle(t_ray ray,t_triangle *triangle);
double hit_square(t_ray ray,t_square *s_square);
double hit_cylinder(t_ray ray,t_cylinder *cylinder);
double hit_disk(t_ray ray,t_disk *disk);
/***********************  LIGHT.C  ***********************/
t_vector ft_specular(t_light *light,t_ray ray,double t,t_object *object);
t_vector ft_diffuse(t_light *light,t_ray ray,double t,t_object *object,t_vector *colors);
t_vector ft_ambient(t_ambient *ambient,t_vector *color);
double ft_shadow(t_object *temp,t_object *object,t_light *light,t_ray ray,double t);

/***********************  PIXEL_COLOR.C  ***********************/
int ft_color_of_pixel(t_ray ray,t_object *object,t_ambient *ambient,t_light *light);
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

# endif