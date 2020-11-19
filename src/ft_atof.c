/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:35:17 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/19 14:31:20 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_atof(const char *str)
{
	double	res;
	double	res2;
	char	*c;
	int		len;
	int		s;

	s = 1;
	c = (char *)str;
	if (*c == '-')
		s = -1;
	res = (double)ft_atoi(c);
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	res2 = (double)ft_atoi(c);
	len = ft_strlen(c);
	while (len--)
		res2 /= 10;
	if (res >= 0 && s > 0)
		return (res + res2);
	else
		return (res - res2);
}

static double	to_double(const char *str, int i, int signe, double resultat)
{
	double sub;
	double dix;
	double div;

	dix = 10;
	div = 0;
	i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		sub = str[i] - '0';
		div = div + sub / dix;
		dix *= 10;
		i++;
	}
	return ((div + resultat) * signe);
}

double			ft_atod(const char *str)
{
	int		i;
	int		sign;
	double	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\f' ||\
			str[i] == '\n' || str[i] == '\v' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1 * sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		return (to_double(str, i, sign, result));
	else
		return (result * sign);
}
