/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 20:10:35 by lbellona          #+#    #+#             */
/*   Updated: 2019/02/25 23:16:50 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int					pr_exit(int key)//, void *param)
{
	if (key == 53)
	{
		exit(0);
	}
	return (0);
}

void				draw_line(t_win_params p, t_point p0, t_point p1)
{
	t_point			delta;
	t_point			sign;
	int				error;

	delta.x = ABS(p1.x - p0.x);
	delta.y = ABS(p1.y - p0.y);
	sign.x = p0.x < p1.x ? 1 : -1;
	sign.y = p0.y < p1.y ? 1 : -1;
	error = delta.x - delta.y;
	mlx_pixel_put(p.mlx_ptr, p.win_ptr, p1.x, p1.y, p.color);
	while (p0.x != p1.x || p0.y != p1.y)
	{
		mlx_pixel_put(p.mlx_ptr, p.win_ptr, p0.x, p0.y, p.color);
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

int					main(int argc, char **argv)
{
	t_win_params	win;
	t_img_params	img;
	t_point			p0;
	t_point			p1;

	argc += 0;
	argv[0][0] = argv[0][0];
	init_win_params(&win);
	win.win_ptr = mlx_new_window(win.mlx_ptr, win.width,
											win.height, "fdf_win");

	img.width = 100;
	img.height = 100;
	img.ptr = mlx_new_image(win.mlx_ptr, img.width, img.height);
	//int i = -1;
	//while (++i < img.width * img.height)
	//{
	//	printf("%d\n", i);
	//	img.ptr[i] = 255;
	//}
	mlx_destroy_image(win.mlx_ptr, img.ptr);
	printf("%d\n", img.width);
	printf("%f\n", fabs(-log10(10.0)));
	p0.x = 1;
	p0.y = 1;
	p1.x = 33;
	p1.y = 123;
	draw_line(win, p0, p1);
	mlx_key_hook(win.win_ptr, pr_exit, (void *)0);
	mlx_loop(win.mlx_ptr);

	printf("%f\n", 1.1);

	//if (argc != 2)
	//	ft_putstr("Usage : ./fdf <filename> [ case_size z_size ]\n");
	//else
	{
	//	if ((fd = open(argv[1], O_RDONLY)) < 0)
	//		return ((int)pr_error());
		/*
		if ((tets = read_2_lst(fd, &tet_num)))
		{
			if (connetivity_is_valid(tets, tet_num))
				solve_map(tets, tet_num);
		}
		else
			return ((int)pr_error());
		*/
	}

	return (0);
}
