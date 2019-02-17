/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 20:10:35 by lbellona          #+#    #+#             */
/*   Updated: 2019/02/18 00:07:30 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int					pr_exit(int key)//, void *param)
{
	if (key == 53)
	{
		//ft_putstr("error\n");
		exit(0);
	}
	return (0);
}

void				draw_line(t_draw_params p, int x0, int y0, int x1, int y1)
{
	t_point			delta;
	t_point			sign;
	int				error;

	delta.x = ABS(x1 - x0);
	delta.y = ABS(y1 - y0);
	sign.x = x0 < x1 ? 1 : -1;
	sign.y = y0 < y1 ? 1 : -1;
	error = delta.x - delta.y;
	mlx_pixel_put(p.mlx_ptr, p.win_ptr, x1, y1, p.color);
	while (x0 != x1 || y0 != y1)
	{
		mlx_pixel_put(p.mlx_ptr, p.win_ptr, x0, y0, p.color);
		if (error * 2 > -delta.y)
		{
			error -= delta.y;
			x0 += sign.x;
		}
		if (error * 2 < delta.x)
		{
			error += delta.x;
			y0 += sign.y;
		}
	}
}

void				init_draw_params(t_draw_params *p)
{
	p->mlx_ptr = mlx_init();
	p->win_width = 0x1F4;
	p->win_height = 0x1F4;
	p->color = 0xFFFFFF;
}

int					main(int argc, char **argv)
{
	t_draw_params	params;

	argc += 0;
	argv[0][0] = argv[0][0];
	init_draw_params(&params);
	params.win_ptr = mlx_new_window(params.mlx_ptr, params.win_width,
											params.win_height, "fdf_win");
	draw_line(params, 1, 1, 13, 123);
	mlx_key_hook(params.win_ptr, pr_exit, (void *)0);
	mlx_loop(params.mlx_ptr);

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
