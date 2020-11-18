/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:24:02 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/18 17:41:03 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene		*ft_scene_init(char *file_name)
{
	extern int	errno;
	t_scene		*scene;

	scene = malloc(sizeof(t_scene));
	scene->fd = open(file_name, O_RDONLY);
	if (scene->fd < 0)
	{
		ft_print_error(strerror(errno));
		exit(EXIT_FAILURE);
	}
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

int			main(int argc, char **argv)
{
	t_scene *scene;

	if (argc > 1)
	{
		scene = ft_scene_init(argv[1]);
		scene = parsing(scene->fd, scene);
		//printf("\n->%d\n",scene->light_number);
		if (argc == 2)
		{
			scene->mlx_ptr = mlx_init();
			scene->win_ptr = mlx_new_window(scene->mlx_ptr,
					scene->resolution.width, scene->resolution.height, argv[1]);
			scene->img = ft_creat_img(scene, scene->mlx_ptr);
			ft_render(scene, scene->camera, 0);
			mlx_put_image_to_window(scene->mlx_ptr,
				scene->win_ptr, scene->img->img, 0, 0);
			mlx_hook(scene->win_ptr, 2, 0, ft_key_press, scene);
			mlx_hook(scene->win_ptr, 17, 0, ft_close, scene);
			mlx_loop(scene->mlx_ptr);
		}
		if (argc > 2 && !ft_strncmp(argv[2], "--save", 7))
			ft_make_image(scene);
		ft_free_scene(scene);
	}
	return (0);
}
