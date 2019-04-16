/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_landscape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:55:36 by lbellona          #+#    #+#             */
/*   Updated: 2019/04/16 23:36:52 by lbellona         ###   ########.fr       */
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
	img->data[p1.x + p1.y] = 0xFFFFFF;
	while (p0.x != p1.x || p0.y != p1.y)
	{
		img->data[p0.x + p0.y] = 0xFFFFFF;
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

void				put_2_img(t_img_params *img, t_map *map)
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
}

/*void				put_2_img(t_img_params *img, t_map *map)
{
	int 			dx;
	int				dy;
	int				i;
	t_point			p0;
	t_point			p1;

	dx = img->width / 2 - MAP_SCALE * map->width / 2;
	dy = (img->height / 2 - MAP_SCALE * map->height / 2) * img->width;
	i = -1;
	while (++i < map->height * map->width)
	{
		if ((i + 1) % map->width != 0)
		{
			p0.x = MAP_SCALE * map->coords[i].x + dx;
			p0.y = MAP_SCALE * map->coords[i].y * img->width + dy;
			p1.x = MAP_SCALE * map->coords[i + 1].x + dx;
			p1.y = MAP_SCALE * map->coords[i + 1].y * img->width + dy;
			draw_line(img, p0, p1);
		}
		else
			printf("%d\n", (i + 1) % map->width);

		//img->data[MAP_SCALE * (map->coords[i].x + map->coords[i].y * img->width) + dxy] = 0xFFFFFF;
	}
}*/

void				rotate_by_x(t_map *map)
{
	int				old_z;
	int				old_y;
	int				i;

	i = -1;
	while (++i < map->height * map->width)
	{
		old_y = map->coords[i].y;
		old_z = map->coords[i].z;
		map->coords[i].y = old_y * cos(0.8) + old_z * sin(0.8);
		//map->coords[i].y = old_y * cos(0.523599) + old_z * sin(0.523599);
	}
}

void				draw_landscape(t_map *map)
{
	t_win_params	win;
	t_img_params	img;
	t_point			p0;
	t_point			p1;

	init_win_params(&win);
	init_img_params(&img, &win);

	printf("%f\n", fabs(-log10(10.0)));
	printf("map_height =  %d\n", map->height);

	//Добавить отрисовку линий
	//добавить проецию
	//добавить работу клавиатуры

	rotate_by_x(map);
	put_2_img(&img, map);
	//rotate_by_x(coords);
	//put_2_img(&img, map, coords);

	/*p0.x = 50;
	p0.y = 50;
	p1.x = 500;
	p1.y = 50;
	draw_line(&img, p0, p1);*/
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, img.ptr, 0, 0);

	//clean_img(&img);
	//mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, img.ptr, 0, 0);

	mlx_key_hook(win.win_ptr, pr_exit, (void *)0);
	mlx_loop(win.mlx_ptr);
}
