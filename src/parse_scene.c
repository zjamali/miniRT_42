/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:50:46 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/24 14:35:44 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		parsing_line_objects(t_scene *scene, char **split)
{
	if (ft_strncmp(split[0], "pl", 2) == 0)
		parsing_plan(split, scene);
	else if (ft_strncmp(split[0], "sp", 2) == 0)
		parsing_sphere(split, scene);
	else if (ft_strncmp(split[0], "sq", 2) == 0)
		parsing_square(split, scene);
	else if (ft_strncmp(split[0], "tr", 2) == 0)
		parsing_triangle(split, scene);
	else if (ft_strncmp(split[0], "cy", 2) == 0)
		parsing_cylinder(split, scene);
}

void		ft_spaces_after_comma(char *line, int i, int j)
{
	if (line[i] == ',' && line[i + 1] == ' ')
	{
		j = i + 1;
		while (line[j] == ' ')
		{
			line[j] = '0';
			j++;
		}
		if (line[j] == '-')
		{
			line[i + 1] = '-';
			line[j] = '0';
		}
	}
}

char		*ft_remake_line(char *line)
{
	int i;
	int j;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\t' || line[i] == '\n' ||
			line[i] == '\v' || line[i] == '\f' || line[i] == '\r')
			line[i] = ' ';
		i++;
	}
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' && line[i + 1] == ',')
		{
			j = i;
			while (line[j] == ' ')
				line[j--] = '.';
		}
		ft_spaces_after_comma(line, i, j);
		i++;
	}
	return (line);
}

int			ft_check_cordinations(char *line)
{
	int i;
	int	a;

	i = 0;
	a = 0;
	while (line[i])
	{
		if (line[i] == ',')
			a++;
		i++;
	}
	if (a > 2)
		return (1);
	if (a == 1)
		return (2);
	return (0);
}

int			ft_check_properties(t_scene *scene, char **line)
{
	int i;
	int result;

	i = 0;
	result = 1;
	while (line[i])
	{
		result = ft_check_cordinations(line[i]);
		if (result == 1)
			ft_print_error(scene, "too much coordination");
		if (result == 2)
			ft_print_error(scene, "missing coodinations");
		i++;
	}
	return (0);
}

void		parsing_line(char *line, t_scene *scene)
{
	char **split;

	line = ft_remake_line(line);
	write(1, line, ft_strlen(line));
	write(1, "\n", 1);
	split = ft_split(line, ' ');
	if (split[1] == NULL)
		ft_print_error(scene, "empty coordination");
	ft_check_properties(scene, split);
	if (split[0][0] == 'R')
		parsing_resolution(split, scene);
	else if (split[0][0] == 'A')
		parsing_ambiant(split, scene);
	else if (split[0][0] == 'l')
		parsing_light(split, scene);
	else if (ft_strncmp(split[0], "c", 2) == 0)
		parsing_camera(split, scene);
	else if (ft_strncmp(split[0], "ts", 2) == 0)
	{
		parse_translation(split, scene);
	}
	else if (ft_strncmp(split[0], "ro", 2) == 0)
		parse_rotation(split, scene);
	parsing_line_objects(scene, split);
}

t_scene		*parsing(int fd, t_scene *scene)
{
	char *line;

	while (get_next_line(fd, &line) > 0)
	{
		if (line[0])
		{
			if (ft_check_line(scene, line))
			{
				parsing_line(line, scene);
			}
			if (line != NULL)
				free(line);
		}
	}
	if (line[0])
	{
		if (ft_check_line(scene, line))
			parsing_line(line, scene);
		free(line);
	}
	ft_check_scene(scene);
	return (scene);
}
