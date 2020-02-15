/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:05:13 by zjamali           #+#    #+#             */
/*   Updated: 2020/02/15 01:06:49 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>


typedef struct s_struct{
	float x,y,z;
}t_vector;

typedef struct s_sphere{
	t_vector pos;
	double  radius;
}t_sphere;

typedef struct s_ray{
	t_vector origin;
	t_vector direction;
}t_ray;

t_vector  vectorsadd(t_vector *v1,t_vector *v2);
t_vector vectorscal(t_vector *v ,double s);
t_vector vectordiv(t_vector *v, double d);
t_vector vectorsSub(t_vector *v1, t_vector *v2);
double vectorsDot(t_vector *v1, t_vector *v2);
double lenght(t_vector *v);
t_vector normalize(t_vector *v);
t_vector vectorsproduit(t_vector *v1,t_vector *v2);

