/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 01:04:46 by zjamali           #+#    #+#             */
/*   Updated: 2020/03/09 19:24:40 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "/usr/X11/include/mlx.h"
#include <mlx.h>
#include <stdio.h>
#include "minirt.h"

void ft_print_error(char *error)
{
	write(2,"Error\n",6);
	write(2,error,ft_strlen(error));
	write(2,"\n",1);
    exit(EXIT_FAILURE);
}