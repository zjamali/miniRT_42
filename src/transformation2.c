/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:50:58 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/17 09:15:48 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_translate_sphere(t_scene *scene)
{
	t_object *obj;
	t_sphere *sp;

	obj = scene->element_to_transform->element;
	sp = obj->object;
	sp->origin = vectorsadd(sp->origin,
					scene->element_to_transform->transform.trans);
	obj->origin = vectorsadd(obj->origin,
					scene->element_to_transform->transform.trans);
}

void	ft_translate_plane(t_scene *scene)
{
	t_object	*obj;
	t_plane		*plan;

	obj = scene->element_to_transform->element;
	plan = obj->object;
	plan->coord = vectorsadd(plan->coord,
					scene->element_to_transform->transform.trans);
	obj->origin = vectorsadd(obj->origin,
					scene->element_to_transform->transform.trans);
}

void	ft_translate_square(t_scene *scene)
{
	t_object	*obj;
	t_square	*square;

	obj = scene->element_to_transform->element;
	square = obj->object;
	square->center = vectorsadd(square->center,
					scene->element_to_transform->transform.trans);
	obj->origin = vectorsadd(obj->origin,
					scene->element_to_transform->transform.trans);
}

void	ft_translate_traiangle(t_scene *scene)
{
	t_object	*obj;
	t_triangle	*trn;

	obj = scene->element_to_transform->element;
	trn = obj->object;
	obj->v3[0] = vectorsadd(obj->v3[0],
					scene->element_to_transform->transform.trans);
	obj->v3[1] = vectorsadd(obj->v3[1],
					scene->element_to_transform->transform.trans);
	obj->v3[2] = vectorsadd(obj->v3[2],
					scene->element_to_transform->transform.trans);
	trn->vectors[0] = vectorsadd(trn->vectors[0],
					scene->element_to_transform->transform.trans);
	trn->vectors[1] = vectorsadd(trn->vectors[1],
					scene->element_to_transform->transform.trans);
	trn->vectors[2] = vectorsadd(trn->vectors[2],
					scene->element_to_transform->transform.trans);
}

void	ft_translate_cylinder(t_scene *scene)
{
	t_object	*obj;
	t_cylinder	*cy;

	obj = scene->element_to_transform->element;
	cy = obj->object;
	obj->origin = vectorsadd(obj->origin,
					scene->element_to_transform->transform.trans);
	cy->coord = vectorsadd(cy->coord,
					scene->element_to_transform->transform.trans);
}
