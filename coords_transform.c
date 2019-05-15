/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 21:23:00 by lbellona          #+#    #+#             */
/*   Updated: 2019/05/15 21:28:36 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				scale_img(int *x, int *y, int *z, t_map *map)
{
	*x *= map->scale;
	*y *= map->scale;
	*z *= map->z_scale;
}

void				rotate_by_x(int *y, int *z, float al)
{
	int				old_z;
	int				old_y;

	old_y = *y;
	old_z = *z;
	*y = (old_y * cos(al) + old_z * sin(al));
	*z = -old_y * sin(al) + old_z * cos(al);
}

void				rotate_by_y(int *x, int *z, float al)
{
	int				old_z;
	int				old_x;

	old_x = *x;
	old_z = *z;
	*x = old_x * cos(al) + old_z * sin(al);
	*z = -old_x * sin(al) + old_z * cos(al);
}

void				iso(int *x, int *y, int z)
{
	int				old_y;
	int				old_x;
	static float	al;

	al = 0.523599;
	old_x = *x;
	old_y = *y;
	*x = (old_x - old_y) * cos(al);
	*y = -z + (old_x + old_y) * sin(al);
}

void				find_offset(t_img_params *img, t_map *map)
{
	img->dxy.x = abs(map->min.x) + (img->width - abs(map->max.x - map->min.x))
															/ 2 + map->x_offset;
	img->dxy.y = (abs(map->min.y) + (img->height - abs(map->max.y - map->min.y))
											/ 2 + map->y_offset) * img->width;
}
