/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_landscape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:55:36 by lbellona          #+#    #+#             */
/*   Updated: 2019/04/20 15:45:01 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void				draw_line(t_img_params *img, t_point p0, t_point p1, t_map *map)
{
	t_point			delta;
	t_point			sign;
	int				error;
	int				dxy;
	//int				dy;


	dxy = img->width / 2 - MAP_SCALE * map->width / 2;
	dxy += (img->height / 2 - MAP_SCALE * map->height / 2) * img->width;
	delta.x = ABS(p1.x - p0.x);
	delta.y = ABS(p1.y - p0.y);
	sign.x = p0.x < p1.x ? 1 : -1;
	sign.y = p0.y < p1.y ? 1 : -1;
	error = delta.x - delta.y;
	img->data[p1.x + p1.y * img->width + dxy] = 0xFFFFFF;
	while (p0.x != p1.x || p0.y != p1.y)
	{
		img->data[p0.x + p0.y * img->width + dxy] = 0xFFFFFF;
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

/*void				put_2_img(t_img_params *img, t_map *map)
{
	int 			dxy;
	int				i;

	dxy = img->width / 2 - MAP_SCALE * map->width / 2;
	dxy += (img->height / 2 - MAP_SCALE * map->height / 2) * img->width;
	i = -1;
	while (++i < map->height * map->width)
	{
		img->data[MAP_SCALE * (map->coords[i].x + map->coords[i].y * img->width)
					+ dxy] = 0xFFFFFF;
	}
}*/

void				put_2_img(t_img_params *img, t_map *map)
{
	//int 			dx;
	//int				dy;
	int				i;
	t_point			p0;
	t_point			p1;

	//dx = img->width / 2 - MAP_SCALE * map->width / 2;
	//dy = (img->height / 2 - MAP_SCALE * map->height / 2) * img->width;
	i = -1;
	while (++i < map->height * map->width)
	{
		if ((i + 1) % map->width != 0)
		{
			p0.x = map->coords[i].x;
			p0.y = map->coords[i].y;
			p1.x = map->coords[i + 1].x;
			p1.y = map->coords[i + 1].y;
			draw_line(img, p0, p1, map);
		}
		if (i < map->width * (map->height - 1))
		{
			p0.x = map->coords[i].x;
			p0.y = map->coords[i].y;
			p1.x = map->coords[i + map->width].x;
			p1.y = map->coords[i + map->width].y;
			draw_line(img, p0, p1, map);
		}

		//img->data[MAP_SCALE * (map->coords[i].x + map->coords[i].y * img->width) + dxy] = 0xFFFFFF;
	}
}

void				rotate_by_x(t_map *map)
{
	int				old_z;
	int				old_y;
	int				i;
	static float	al;

	i = -1;
	al = 0.5708;
	while (++i < map->height * map->width)
	{
		old_y = map->coords[i].y;
		old_z = map->coords[i].z;
		map->coords[i].y = old_y * cos(al) - old_z * sin(al);
		map->coords[i].z = -old_y * sin(al) - old_z * cos(al);
	}
	//al += 0.1;
}

void				rotate_by_y(t_map *map)
{
	int				old_z;
	int				old_x;
	int				i;
	static float	al;

	i = -1;
	al = 0.5708;
	while (++i < map->height * map->width)
	{
		old_x = map->coords[i].x;
		old_z = map->coords[i].z;
		map->coords[i].x = old_x * cos(al) + old_z * sin(al);
		map->coords[i].z = -old_x * sin(al) + old_z * cos(al);
	}
	//al += 0.1;
}

void				iso(t_map *map)
{
	int				old_y;
	int				old_x;
	int				i;
	static float	al;

	i = -1;
	al = 0.5708;
	while (++i < map->height * map->width)
	{
		old_x = map->coords[i].x;
		old_y = map->coords[i].y;
		map->coords[i].x = (old_x - old_y) * cos(al);
		map->coords[i].y = -map->coords[i].z + (old_x + old_y) * sin(al);
	}
	al += 0.1;
}

void				scale_img1(t_map *map)
{
	int				i;

	i = -1;
	while (++i < map->height * map->width)
	{
		map->coords[i].x *= MAP_SCALE;
		map->coords[i].y *= MAP_SCALE;
		//map->coords[i].z *= MAP_SCALE;
	}
}

/*
void				draw(t_fdf *fdf)
{
	int				i;

	i = -1;
	while (++i < map->height * map->width)
	{
		map->coords[i].x *= MAP_SCALE;
		map->coords[i].y *= MAP_SCALE;
		//map->coords[i].z *= MAP_SCALE;
	}
}*/

void				draw_landscape(t_fdf *fdf)
{
	init_win_params(&fdf->win);
	init_img_params(&fdf->img, &fdf->win);

	//Добавить отрисовку линий
	//добавить проекцию
	//добавить работу клавиатуры

	scale_img1(&fdf->map);
	rotate_by_x(&fdf->map);
	//rotate_by_y(map);
	//iso(map);
	put_2_img(&fdf->img, &fdf->map);

	mlx_put_image_to_window(fdf->win.mlx_ptr, fdf->win.win_ptr, fdf->img.ptr, 0, 0);

	//clean_img(&img);
	//mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, img.ptr, 0, 0);

	//mlx_key_hook(win.win_ptr, pr_exit, (void *)0);

	mlx_hook(fdf->win.win_ptr, 2, 0, pr_exit, fdf);
	mlx_loop(fdf->win.mlx_ptr);
}
