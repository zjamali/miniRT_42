/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:05:13 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/24 14:38:37 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <errno.h>
# include <string.h>
# include "get_next_line.h"
# include "vectors.h"
# include "scene.h"
# include "transformation.h"
# include "intersection.h"
# include "parsing.h"
# define PI 3.1415926535897932



#include <stdio.h>

typedef struct		s_bmp
{
	unsigned char	header[54];
	unsigned int	pixel_bytes_per_row;
	unsigned int	padding_bytes_per_row;
	unsigned int	*size_of_file_entry;
	unsigned int	*width_entry;
	unsigned int	*height_entry;
	unsigned char	zeroes[3];
	int				fd;
	int				row;
}					t_bmp;

void		parsing_light(char **lit, t_scene *scene);
void		parsing_camera(char **cam, t_scene *scene);
void		ft_check_camera(t_scene *scene, char **origin, char **orient);
void		parsing_ambiant(char **amb, t_scene *scene);


double				ft_atod(const char *str);
int					ft_chech_pixel_in_dark(t_scene *scene,
						t_object *closet_object, double t);
t_vector 			ft_calcule_pixel_color(t_scene *scene,
							t_object *closet_object, double t);
double				ft_hit_objects(t_object *temps, t_ray p_ray);
void				ft_free_scene(t_scene *scene);
void				ft_free_pixels(t_scene *scene);
void				ft_free_objects(t_object *objects);
void				ft_free_cameras(t_camera *cam);
void				ft_free_lights(t_light *lights);
void				ft_render(t_scene *scene, t_camera *camera, int n);
t_ray				*ft_ray_creating(t_scene *scene, t_camera *camera,
										int i, int j);
void				my_mlx_pixel_put(t_imag *img, int x, int y, int color);
t_camera			*ft_wich_camera(t_scene *scene, int keycode);
t_pixel				int_color_to_pixel(int color);
void				ft_make_image(t_scene *scene);
void				ft_write_header(t_bmp *image, t_scene *scene);
void				ft_write_bmp(t_scene *scene);
void				ft_creat_image_pixels_array(t_scene *scene);
void				ft_print_error(t_scene *scene, char *error);
int					ft_key_press(int keycode, t_scene *scene);
int					ft_close(t_scene *scene);
char				**ft_split(char const *s, char c);
void				*ft_memset(void *b, int c, size_t len);
int					ft_atoi(const char *str);
double				ft_atof(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
double				max(double a, double b);
double				min(double a, double b);

#endif
