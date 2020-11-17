/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:37:24 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/17 14:31:22 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		my_mlx_pixel_put(t_imag *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(int*)dst = color;
}

t_imag		*ft_creat_img(t_scene *scene, void *mlx_ptr)
{
	t_imag *imag;

	imag = malloc(sizeof(t_imag));
	imag->img = mlx_new_image(mlx_ptr, scene->resolution.width,
			scene->resolution.height);
	imag->addr = mlx_get_data_addr(imag->img, &imag->bits_per_pixel,
			&imag->line_length, &imag->endian);
	return (imag);
}

t_camera	*ft_wich_camera(t_scene *scene, int keycode)
{
	static t_camera *cam;

	if (cam == NULL)
		cam = scene->camera;
	if (keycode == 124 && cam->next != NULL)
		cam = cam->next;
	if (keycode == 123 && cam->prev != NULL)
		cam = cam->prev;
	return (cam);
}

int			ft_key_press(int keycode, t_scene *scene)
{
	t_camera	*camera;

	camera = NULL;
	if (keycode == 53)
	{
		ft_free_scene(scene);
		exit(0);
	}
	else if (keycode == 123 || keycode == 124)
	{
		camera = ft_wich_camera(scene, keycode);
		ft_render(scene, camera, 0);
		mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr,
				scene->img->img, 0, 0);
	}
	return (0);
}

int			ft_close(t_scene *scene)
{
	ft_free_scene(scene);
	exit(0);
}
