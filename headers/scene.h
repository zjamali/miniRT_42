/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:21:52 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/17 13:07:59 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef struct		s_imag
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}					t_imag;

typedef struct		s_sphere
{
	t_vector	origin;
	double		radius;
	t_vector	color;
}					t_sphere;

typedef struct		s_plane
{
	t_vector	coord;
	t_vector	orientation;
	t_vector	color;
}					t_plane;

typedef struct		s_triangle
{
	t_vector	vectors[3];
	t_vector	color;
}					t_triangle;

typedef struct		s_square
{
	t_vector	center;
	t_vector	normal;
	double		edge_size;
	t_vector	color;
}					t_square;

typedef struct		s_cylinder
{
	t_vector	coord;
	t_vector	normal;
	double		height;
	double		diameter;
	t_vector	color;
}					t_cylinder;

typedef struct		s_ray
{
	t_vector	origin;
	t_vector	direction;
}					t_ray;

typedef struct		s_camera
{
	t_vector		lookfrom;
	t_vector		orientaion;
	double			fov;
	struct s_camera	*next;
	struct s_camera	*prev;
}					t_camera;

typedef struct		s_object
{
	void			*object;
	t_vector		color;
	t_vector		origin;
	t_vector		orientation;
	char			object_type;
	t_vector		v3[3];
	double			size;
	double			radius;
	double			diameter;
	struct s_object	*next;
}					t_object;

typedef struct		s_ambient
{
	double		intensity;
	t_vector	color;
}					t_ambient;

typedef struct		s_light
{
	t_vector		origin;
	double			intensity;
	t_vector		color;
	struct s_light	*next;

}					t_light;

typedef	struct		s_resolution
{
	int				height;
	int				width;
}					t_resolution;

typedef struct		s_pixel
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
}					t_pixel;

typedef struct		s_trans
{
	t_vector		trans;
	t_vector		rot;
}					t_trans;

typedef struct		s_elmt_to_tran
{
	char			wich_element;
	void			*element;
	t_trans			transform;
}					t_elmt_to_tran;

typedef struct		s_scene
{
	t_ambient		ambient;
	t_resolution	resolution;
	t_camera		*camera;
	t_light			*light;
	int				color_of_pixel;
	int				fd;
	t_ray			*ray;
	t_object		*objects;
	t_imag			*img;
	void			*mlx_ptr;
	void			*win_ptr;

	t_elmt_to_tran	*element_to_transform;

	t_pixel			**pixels;
}					t_scene;

t_imag				*ft_creat_img(t_scene *scene, void *mlx_ptr);
t_vector			ft_camera_ray(t_scene *scene, t_camera
									*camera, double x, double y);
t_vector			ft_specular(t_scene *scene, double t, t_object *object);
t_vector			ft_diffuse(t_scene *scene, double t, t_object *object);
t_vector			ft_ambient(t_ambient ambient, t_vector color);
double				ft_shadow(t_scene *scene, double t,
											t_object *closet_object);
int					ft_color_of_pixel(t_scene *scene);
double				rgbconvert(int ir, int ig, int ib);

#endif
