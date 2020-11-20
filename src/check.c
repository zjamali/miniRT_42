/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:10:33 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/20 14:58:22 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_check_element(t_scene *scene, char *line, int i)
{
	char	**split;

	//split = &line;
	split = ft_split(line + i, ' ');
	i = 0;
	if (split[i][0] != 'R' && split[i][0] != 'A' && split[i][0] != 'l'
		&& ft_strncmp(split[i], "c", 2) && ft_strncmp(split[i], "pl", 2) &&
		ft_strncmp(split[i], "sp", 2) && ft_strncmp(split[i], "sq", 2) &&
		ft_strncmp(split[i], "tr", 2) && ft_strncmp(split[i], "cy", 2) &&
		ft_strncmp(split[i], "rot", 3) && ft_strncmp(split[i], "tra", 3) )
		ft_print_error(scene, "unknown element in the scene.");
}

void		ft_check_symboles(t_scene *scene, char *line, int i)
{
	while(line[i] != '\0')
	{
		write(1,&line[i],ft_strlen(&line[i]));
		write(1,"\n",1);
		if (line[i] == ' ' || line[i] == '-' || line[i] == ',' || line[i] == '.' 
		|| (line[i] >= '0' && line[i] <= '9') || line[i] == '+' || 
		line[i] == 'R' || line[i] == 'A' || line[i] == 'l' || line[i] == '\t' || line[i] == 'c' ||
		line[i] == 'p' || line[i] == 'l' || line[i] == 's' || line[i] == 'q' || line[i] == 'y' ||
		line[i] == 't' || line[i] == 'r' || line[i] == 'o')
		{
			i++;
		}
		else
			ft_print_error(scene,"undifined symbole");
		
	}
	
}

int			ft_check_line(t_scene *scene, char *line)
{
	
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
		return (0);
	ft_check_element(scene, line, i);
	ft_check_symboles(scene,line,i);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',' && line[i + 1] == ',')
			ft_print_error(scene, "two comma in line");
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
		ft_print_error(scene, "No camera in the scene,you need at least\
		one camera in the scene.");
	if (scene->resolution.height == 0 && scene->resolution.width == 0)
		ft_print_error(scene, "you have to specify the resolution.");
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
	if (coord[0][0] == ' ' || coord[1] != NULL )
	{
		return (0);
	}
	if (coord[0] == NULL || coord[1] == NULL || coord[2] == NULL)
		return (1);
	return (0);
}
