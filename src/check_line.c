/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:20:53 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/24 13:24:41 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_check_elemet_lenght(t_scene *scene, char *element)
{
	int		i;
	char	line[3];
	char	c;

	i = 0;
	while (element[i])
	{
		c = element[i];
		if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
			line[i] = c;
		i++;
	}
	if (ft_strlen(line) > 2)
		ft_print_error(scene, "unknown element in the scene!!!!!!.");
}

void		ft_check_element(t_scene *scene, char *line, int i)
{
	char	**split;

	split = ft_split(line + i, ' ');
	i = 0;
	ft_check_elemet_lenght(scene, split[i]);
	if (split[i][0] != 'R' && split[i][0] != 'A' && split[i][0] != 'l'
		&& ft_strncmp(split[i], "c", 2) && ft_strncmp(split[i], "pl", 2) &&
		ft_strncmp(split[i], "sp", 2) && ft_strncmp(split[i], "sq", 2) &&
		ft_strncmp(split[i], "tr", 2) && ft_strncmp(split[i], "cy", 2) &&
		ft_strncmp(split[i], "ro", 2) && ft_strncmp(split[i], "ts", 2))
	{
		ft_print_error(scene, "unknown element in the scene.");
	}
}

void		ft_check_symboles(t_scene *scene, char *line)
{
	int i;
	int	bol;

	i = 0;
	bol = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '-' || line[i] == ',' || line[i] == '.'
		|| line[i] == '+' || line[i] == 'R'
		|| line[i] == 'A' || line[i] == 'l' || line[i] == '\t' || line[i] == 'c'
		|| line[i] == 'p' || line[i] == 'l' || line[i] == 's' || line[i] == 'q'
		|| line[i] == 'y' || line[i] == 't' || line[i] == 'r' || line[i] == 'o'
		|| (line[i] >= '0' && line[i] <= '9'))
		{
			if (line[i] == ',' && bol == 0)
				ft_print_error(scene, "missing cord");
			else if (line[i] == ',')
				bol = 0;
			if (line[i] >= '0' && line[i] <= '9')
				bol = 1;
			i++;
		}
		else
			ft_print_error(scene, "undifined symbole");
	}
}

int			ft_check_line(t_scene *scene, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\v' ||
	line[i] == '\f' || line[i] == '\r')
		i++;
	if (line[i] == '\0')
		return (0);
	ft_check_element(scene, line, i);
	ft_check_symboles(scene, line);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',' && line[i + 1] == ',')
			ft_print_error(scene, "two comma in line");
		i++;
	}
	return (1);
}
