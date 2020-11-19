/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:10:33 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/19 10:55:52 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_check_element(char *line)
{
	char **split;
	int i;
	
	i = 0;
	split = ft_split(line, ' ');
	if (split[0][0] != 'R' && split[0][0] != 'A' && split[0][0] != 'l'
		&& ft_strncmp(split[0], "c", 2) && ft_strncmp(split[0], "pl", 2) &&
		ft_strncmp(split[0], "sp", 2) && ft_strncmp(split[0], "sq", 2) &&
		ft_strncmp(split[0], "tr", 2) && ft_strncmp(split[0], "cy", 2) &&
		ft_strncmp(split[0], "rot", 3) && ft_strncmp(split[0], "tra", 3) && 
		(split[0][0] == ' '))
		ft_print_error("unknown element in the scene.");
}

int			ft_check_line(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
		return (0);
	ft_check_element(line);
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != ',' &&
				line[i] != '.' && (line[i] < '0' && line[i] > '9'))
			ft_print_error("undifined symbole in the scene file");
		i++;
	}
	i = 1;
	while (line[i] != '\0')
	{
		if (line[i] == ',' && line[i + 1] == ',')
			ft_print_error("two comma in line");
		i++;
	}
	return (1);
}

void		ft_check_scene(t_scene *scene)
{
	int height;
	int width;

	width = 5120;
	height = 2880;
	if (scene->camera == NULL)
		ft_print_error("No camera in the scene,you need at least\
		one camera in the scene.");
	if (scene->resolution.height == 0 && scene->resolution.width == 0)
		ft_print_error("you have to specify the resolution.");
	if (scene->resolution.height > height)
		scene->resolution.height = height;
	if (scene->resolution.width > width)
		scene->resolution.width = width;
}

int			ft_check_color(char **color)
{
	t_vector colors;

	if (color[0] == NULL || color[1] == NULL || color[2] == NULL)
	{
		return (1);
	}
	else
	{
		colors = ft_parse_color(color);
		if (colors.x < 0 || colors.x > 255 || colors.y < 0 || colors.y > 255 ||
				colors.z < 0 || colors.z > 255)
			return (1);
	}
	return (0);
}

int			ft_check_coords(char **coord)
{
	
	if (coord[0][0] == ' ' || coord[1] != NULL)
	{
		return 0;
	}
	if (/*coord[0] == NULL || coord[1] == NULL || */coord[2] == NULL)
	{
		write(1,"jjj",3);
		return (1);
	}
	return (0);
}
