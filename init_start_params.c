/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_start_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 21:31:42 by lbellona          #+#    #+#             */
/*   Updated: 2019/05/15 22:06:18 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				init_win_params(t_win_params *win)
{
	win->mlx_ptr = mlx_init();
	win->width = WIN_WIDTH;
	win->height = WIN_HEIGHT;
	win->color = POINT_COLOR;
	win->win_ptr = mlx_new_window(win->mlx_ptr, win->width,
														win->height, "fdf_prj");
}

void				init_img_params(t_img_params *img, t_win_params *win)
{
	img->width = WIN_WIDTH;
	img->height = WIN_HEIGHT;
	img->ptr = mlx_new_image(win->mlx_ptr, img->width, img->height);
	img->data = (int*)mlx_get_data_addr(img->ptr, &(img->bpp), &(img->size_l),
																&(img->endian));
}

int					auto_map_scale(t_map *map)
{
	int				scale;

	scale = (int)(START_MAP_SCALE_PERCENT *
				fmax(WIN_WIDTH, WIN_HEIGHT)) / fmax(map->width, map->height);
	return (scale > 1 ? scale : 1);
}

void				init_map_params(t_map *map)
{
	map->min.x = 999999999;
	map->max.x = 0;
	map->min.y = 999999999;
	map->max.y = 0;
	map->alpha_x = 0.0;
	map->alpha_y = 0.0;
	map->scale = auto_map_scale(map);
	map->z_scale = START_Z_SCALE;
	map->x_offset = 0;
	map->y_offset = 0;
	map->proj_type = PARALLEL;
}

void				cpy_inp_coords(t_fdf *fdf)
{
	int i;

	fdf->map.min.x = 999999999;
	fdf->map.max.x = -999999999;
	fdf->map.min.y = 999999999;
	fdf->map.max.y = -999999999;
	i = -1;
	while (++i < fdf->map.height * fdf->map.width)
	{
		fdf->map.coords[i].x = fdf->map.inp_coords[i].x;
		fdf->map.coords[i].y = fdf->map.inp_coords[i].y;
		fdf->map.coords[i].z = fdf->map.inp_coords[i].z;
	}
}
