/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:24:02 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/23 20:25:49 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double		min(double a, double b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

void		ft_check_file_name(char *file_name, t_scene *scene)
{
	int i;

	i = 0;
	while (file_name[i] != '\0')
		i++;
	if (ft_strncmp(file_name + i - 2, "rt", 2))
	{
		ft_print_error(scene, "file extention not .rt ");
	}
}

t_scene		*ft_scene_init(char *file_name)
{
	extern int	errno;
	t_scene		*scene;

	scene = (t_scene*)malloc(sizeof(t_scene));
	if (!scene)
		ft_print_error(scene, "allocation error");
	ft_memset((void*)scene, 0, sizeof(t_scene));
	scene->fd = open(file_name, O_RDONLY);
	if (scene->fd < 0)
		ft_print_error(scene, strerror(errno));
	ft_check_file_name(file_name, scene);
	scene->resolution.height = 0;
	scene->resolution.width = 0;
	scene->ambient.intensity = -1;
	scene->camera = NULL;
	scene->light = NULL;
	scene->objects = NULL;
	scene->img = NULL;
	scene->element_to_transform = NULL;
	scene->light_number = 0;
	return (scene);
}

void		ft_make_window(t_scene *scene, char *window_name)
{
	scene->mlx_ptr = mlx_init();
	scene->win_ptr = mlx_new_window(scene->mlx_ptr,
	scene->resolution.width, scene->resolution.height, window_name);
	scene->img = ft_creat_img(scene, scene->mlx_ptr);
	ft_render(scene, scene->camera, 0);
	mlx_put_image_to_window(scene->mlx_ptr,
				scene->win_ptr, scene->img->img, 0, 0);
}

int			main(int argc, char **argv)
{
	t_scene *scene;

	scene = NULL;
	if (argc > 1 && argc < 4)
	{
		scene = ft_scene_init(argv[1]);
		scene = parsing(scene->fd, scene);
		if (argc == 2)
		{
			ft_make_window(scene, argv[1]);
			mlx_hook(scene->win_ptr, 2, 0, ft_key_press, scene);
			mlx_hook(scene->win_ptr, 17, 0, ft_close, scene);
			mlx_loop(scene->mlx_ptr);
		}
		if (argc > 2 && !ft_strncmp(argv[2], "--save", 7))
			ft_make_image(scene);
		else
			ft_print_error(scene, "do you mean '--save' as third argument!");
		ft_free_scene(scene);
	}
	else
		ft_print_error(scene, "you need to check arguments!!!!!");
	return (0);
}
