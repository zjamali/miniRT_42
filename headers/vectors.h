/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:54:59 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/17 11:04:16 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct	s_vector
{
	float x;
	float y;
	float z;
}				t_vector;

t_vector		bzero_vector(void);
double			lenght(t_vector v);
t_vector		normalize(t_vector v);
t_vector		vectorsproduit(t_vector v1, t_vector v2);
t_vector		vecttorscross(t_vector v1, t_vector v2);
t_vector		vectorsadd(t_vector v1, t_vector v2);
t_vector		vectorscal(t_vector v, double s);
t_vector		vectordiv(t_vector v, double d);
t_vector		vectorssub(t_vector v1, t_vector v2);
double			vectorsdot(t_vector v1, t_vector v2);

#endif
