/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:35:17 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/19 14:14:11 by zjamali          ###   ########.fr       */
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
