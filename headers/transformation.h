/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:05:08 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/17 13:09:20 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATION_H
# define TRANSFORMATION_H

void		ft_make_rotation(t_scene *scene);
t_vector	ft_calcule_rotaion(t_vector orientation, t_vector rotaion);
t_vector	ft_calcule_rotaion_x_axis(double angle, t_vector orientation);
t_vector	ft_calcule_rotaion_y_axis(double angle, t_vector orientation);
t_vector	ft_calcule_rotaion_z_axis(double angle, t_vector orientation);
void		ft_make_translation(t_scene *scene);
void		ft_translate_cylinder(t_scene *scene);
void		ft_translate_traiangle(t_scene *scene);
void		ft_translate_square(t_scene *scene);
void		ft_translate_plane(t_scene *scene);
void		ft_translate_sphere(t_scene *scene);

#endif
