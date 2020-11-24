/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:10:36 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/24 17:55:08 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "vectors.h"
# include "scene.h"

typedef struct	s_obj_properties
{
	char		**origin;
	char		**normal;
	double		diameter;
	double		size;

	char		**cord1;
	char		**cord2;
	char		**cord3;
	char		**color;
}				t_obj_properties;

t_scene			*parsing(int fd, t_scene *scene);
void			ft_check_element(t_scene *scene, char *line, int i);
int				ft_check_line(t_scene *scene, char *line);
void			ft_check_scene(t_scene *scene);
void			ft_lstadd_back_camera(t_camera **alst, t_camera *news);
t_light			*ft_lstlast_light(t_light *lst);
void			ft_lstadd_back(t_object **alst, t_object *news);
void			ft_lstadd_back_light(t_light **alst, t_light *news);
int				ft_check_normal(char **norm);
t_vector		ft_parse_normal(char **norm);
t_vector		ft_parse_color(char **colors);
t_vector		ft_parse_coord(char **coord);
void			ft_element_can_transforme(t_scene *scene, char wich_element,
											void *the_element);
void			ft_check_plane(t_scene *scene, t_obj_properties obj);
void			ft_check_sphere(t_scene *scene, t_obj_properties obj);
void			ft_check_square(t_scene *scene, t_obj_properties obj);
void			ft_check_triangle(t_scene *scene, t_obj_properties obj);
void			ft_check_cylinder(t_scene *scene, t_obj_properties obj);
void			parsing_resolution(char **resol, t_scene *scene);
void			parsing_ambiant(char **amb, t_scene *scene);
void			parsing_camera(char **cam, t_scene *scene);
void			parsing_light(char **light_line, t_scene *scene);
void			parsing_sphere(char **sph, t_scene *scene);
void			parsing_plan(char **pl, t_scene *scene);
void			parsing_square(char **sqr, t_scene *scene);
void			parsing_triangle(char **tr, t_scene *scene);
void			parsing_cylinder(char **cy, t_scene *scene);
void			ft_check_scene(t_scene *scene);
int				ft_check_color(char **color);
int				ft_check_coords(char **coord);
void			parse_rotation(char **line, t_scene *scene);
void			parse_translation(char **line, t_scene *scene);

#endif
