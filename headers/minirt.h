/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:05:13 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/17 12:46:38 by zjamali          ###   ########.fr       */
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

void				ft_render(t_scene *scene, t_camera *camera, int n);
t_ray				*ft_ray_creating(t_scene *scene, t_camera *camera,
										int i, int j);
void				my_mlx_pixel_put(t_imag *img, int x, int y, int color);
t_camera			*ft_wich_camera(t_scene *scene, int keycode);
t_pixel				int_color_to_pixel(int color);
void				ft_write_header(t_bmp *image, t_scene *scene);
void				ft_write_bmp(t_scene *scene);
void				ft_creat_image_pixels_array(t_scene *scene);
void				ft_print_error(char *error);
int					ft_key_press(int keycode, t_scene *scene);
int					ft_close(t_scene *scene);
char				**ft_split(char const *s, char c);
int					ft_atoi(const char *str);
double				ft_atof(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
double				max(double a, double b);
double				min(double a, double b);

#endif
