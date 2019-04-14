/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_landscape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:55:36 by lbellona          #+#    #+#             */
/*   Updated: 2019/04/14 23:18:20 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void				draw_line(t_img_params *img, t_point p0, t_point p1)
{
	t_point			delta;
	t_point			sign;
	int				error;

	delta.x = ABS(p1.x - p0.x);
	delta.y = ABS(p1.y - p0.y);
	sign.x = p0.x < p1.x ? 1 : -1;
	sign.y = p0.y < p1.y ? 1 : -1;
	error = delta.x - delta.y;
	img->data[p1.x + p1.y * img->width] = 0xFFFFFF;
	while (p0.x != p1.x || p0.y != p1.y)
	{
		img->data[p0.x + p0.y * img->width] = 0xFFFFFF;
		if (error * 2 > -delta.y)
		{
			error -= delta.y;
			p0.x += sign.x;
		}
		if (error * 2 < delta.x)
		{
			error += delta.x;
			p0.y += sign.y;
		}
	}
}

void				init_win_params(t_win_params *win)
{
	win->mlx_ptr = mlx_init();
	win->width = WIN_WIDTH;
	win->height = WIN_HEIGHT;
	win->color = 0xFFFFFF;
	win->win_ptr = mlx_new_window(win->mlx_ptr, win->width,
														win->height, "fdf_prj");
}

void				init_img_params(t_img_params *img, t_win_params *win)
{
	img->width = WIN_WIDTH;
	img->height = WIN_HEIGHT;
	img->ptr = mlx_new_image(win->mlx_ptr, img->width, img->height);
	img->data = (int*)mlx_get_data_addr(img->ptr, &(img->bpp), &(img->size_l), &(img->endian));
}

void				clean_img(t_img_params *img)
{
	int 			i;

	i = -1;
	while (++i < img->width * img->height)
			img->data[i] = 0;
}

void				put_2_img(t_img_params *img, t_3d_size *map_size,
															t_3d_coords *coords)
{
	int 			dxy;

	dxy = img->width / 2 - MAP_SCALE * map_size->width / 2;
	dxy += (img->height / 2 - MAP_SCALE * map_size->height / 2) * img->width;
	while (coords)
	{
		img->data[MAP_SCALE * (coords->x + coords->y * img->width)
					+ dxy] = 0xFFFFFF;
		coords = coords->next;
	}
}

void				rotate_by_x(t_3d_coords *coords)
{
	int				old_z;
	int				old_y;

	while (coords)
	{
		old_y = coords->y;
		old_z = coords->z;
		coords->y = old_y * cos(0.8) + old_z * sin(0.8);
		//coords->y = old_y * cos(0.523599) + old_z * sin(0.523599);
		coords = coords->next;
	}
}
void				draw_landscape(t_3d_coords *coords, t_3d_size *map_size)
{
	t_win_params	win;
	t_img_params	img;
	t_point			p0;
	t_point			p1;

	init_win_params(&win);
	init_img_params(&img, &win);

	printf("%f\n", fabs(-log10(10.0)));
	printf("map_height =  %d\n", map_size->height);

	//Положить в массив для появления возможности перехода к соседней точке
	//Добавить отрисовку линий
	//добавить проецию
	//добавить работу клавиатуры

	rotate_by_x(coords);
	put_2_img(&img, map_size, coords);

	/*p0.x = 1;
	p0.y = 1;
	p1.x = 33;
	p1.y = 123;
	draw_line(&img, p0, p1);*/
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, img.ptr, 0, 0);

	//clean_img(&img);
	//mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, img.ptr, 0, 0);

	mlx_key_hook(win.win_ptr, pr_exit, (void *)0);
	mlx_loop(win.mlx_ptr);
}
