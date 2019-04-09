/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_landscape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:55:36 by lbellona          #+#    #+#             */
/*   Updated: 2019/04/09 21:59:24 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void				draw_line(t_img_params *img, t_point p0, t_point p1)
//(t_win_params p, t_point p0, t_point p1)
{
	t_point			delta;
	t_point			sign;
	int				error;

	delta.x = ABS(p1.x - p0.x);
	delta.y = ABS(p1.y - p0.y);
	sign.x = p0.x < p1.x ? 1 : -1;
	sign.y = p0.y < p1.y ? 1 : -1;
	error = delta.x - delta.y;
	img->data[p1.x + p1.y * img->width] = 0x00FFFF;
	//mlx_pixel_put(p.mlx_ptr, p.win_ptr, p1.x, p1.y, p.color);
	while (p0.x != p1.x || p0.y != p1.y)
	{
		img->data[p0.x + p0.y * img->width] = 0x00FFFF;
		//mlx_pixel_put(p.mlx_ptr, p.win_ptr, p0.x, p0.y, p.color);
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

void				init_win_params(t_win_params *p)
{
	p->mlx_ptr = mlx_init();
	p->width = 0x1F4;
	p->height = 0x1F4;
	p->color = 0xFFFFFF;
}

void				clean_img(t_img_params *img)
{
	int 			i;

	i = -1;
	while (++i < img->width * img->height)
			img->data[i] = 0;
}

void				draw_landscape(t_3d_coords *coords)
{
	t_win_params	win;
	t_img_params	img;
	t_point			p0;
	t_point			p1;

	init_win_params(&win);
	win.win_ptr = mlx_new_window(win.mlx_ptr, win.width,
											win.height, "fdf_win");

	img.width = 0x1F4;
	img.height = 0x1F4;
	img.ptr = mlx_new_image(win.mlx_ptr, img.width, img.height);
	img.data = (int*)mlx_get_data_addr(img.ptr, &img.bpp, &img.size_l, &img.endian);

	//img.data[0] = 0xFFFFFF;//(char)255;
	//img.data[1] = (char)255;
	//img.data[2] = (char)255;
	//img.data[3] = (char)0;

	printf("%f\n", fabs(-log10(10.0)));

	p0.x = 1;
	p0.y = 1;
	p1.x = 33;
	p1.y = 123;

	//draw_line(win, p0, p1);
	draw_line(&img, p0, p1);
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, img.ptr, 0, 0);

	//clean_img(&img);
	//mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, img.ptr, 0, 0);

	mlx_key_hook(win.win_ptr, pr_exit, (void *)0);
	mlx_loop(win.mlx_ptr);
}
