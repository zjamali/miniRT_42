/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:24:02 by zjamali           #+#    #+#             */
/*   Updated: 2020/03/14 18:21:01 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void parsing_resolution(char **resol,t_scene *scene)
{
    t_resolution *resolution;
    resolution = malloc(sizeof(t_resolution));
    resolution->width = ft_atoi(resol[1]);
    resolution->height = ft_atoi(resol[2]);
    scene->resolution = resolution;
}

void parsing_ambiant(char **amb,t_scene *scene)
{
    t_ambient *ambient;
    char **color;

    ambient = malloc(sizeof(t_ambient));
    ambient->intensity = ft_atof(amb[1]);

    color  = ft_split(amb[2],',');
    ambient->color.x = ft_atoi(color[0]);
    ambient->color.y = ft_atoi(color[1]);
    ambient->color.z = ft_atoi(color[2]);


    scene->ambient = ambient;
}

void parsing_camera(char **cam,t_scene *scene)
{
    char **origin;
    char **normal;

    t_camera *camera;
    camera = malloc(sizeof(t_camera));

    origin  = ft_split(cam[1],',');
    camera->lookfrom.x = ft_atoi(origin[0]);
    camera->lookfrom.y = ft_atoi(origin[1]);
    camera->lookfrom.z = ft_atoi(origin[2]);

    normal  = ft_split(cam[2],',');
    camera->orientaion.x = ft_atoi(normal[0]);
    camera->orientaion.y = ft_atoi(normal[1]);
    camera->orientaion.z = ft_atoi(normal[2]);    

    camera->fov = ft_atoi(cam[3]);

    scene->camera = camera;
}
void parsing_line(char *line,t_scene *scene)
{
    char **split;
    split = ft_split(line, ' ');
    if (ft_strncmp(split[0],"R",1) == 0)
        parsing_resolution(split,scene);
   else if (ft_strncmp(split[0],"A",1) == 0)
        parsing_ambiant(split,scene);
    else if (ft_strncmp(split[0],"c",2) == 0)
        parsing_camera(split,scene);
}


t_scene *parsing(int fd)
{
    t_scene *scene;
    scene = malloc(sizeof(t_scene));
    char *line;
    while(get_next_line(fd,&line) > 0)
		{
            parsing_line(line,scene);
            printf("\n");
			free(line);
		}
    return scene;
}