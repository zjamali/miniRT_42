/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:32:09 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/24 17:54:36 by zjamali          ###   ########.fr       */
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
