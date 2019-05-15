/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_landscape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:55:36 by lbellona          #+#    #+#             */
/*   Updated: 2019/05/15 22:12:16 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					handle_key(int key, t_fdf *fdf)
{
	key == 53 ? exit(0) : (void)0;
	key == 84 ? fdf->map.alpha_x += 0.1 : (void)0;
	key == 87 ? fdf->map.alpha_x -= 0.1 : (void)0;
	key == 83 ? fdf->map.alpha_y -= 0.1 : (void)0;
	key == 85 ? fdf->map.alpha_y += 0.1 : (void)0;
	key == 69 ? fdf->map.scale += 1 : (void)0;
	(key == 78 && fdf->map.scale > 0) ? fdf->map.scale -= 1 : (void)0;
	(key == 27 && fdf->map.z_scale > 0) ? fdf->map.z_scale -= 1 : (void)0;
	key == 24 ? fdf->map.z_scale += 1 : (void)0;
	key == 123 ? fdf->map.x_offset -= 10 : (void)0;
	key == 124 ? fdf->map.x_offset += 10 : (void)0;
	key == 126 ? fdf->map.y_offset -= 10 : (void)0;
	key == 125 ? fdf->map.y_offset += 10 : (void)0;
	key == 35 ? fdf->map.proj_type *= -1 : (void)0;
	clean_img(&fdf->img);
	draw(fdf);
	return (0);
}

void				clean_img(t_img_params *img)
{
	int				i;

	i = -1;
	while (++i < img->width * img->height)
		img->data[i] = 0;
}

void				put_2_img(t_img_params *img, t_map *map)
{
	int				i;
	t_point			p0;
	t_point			p1;

	i = -1;
	while (++i < map->height * map->width)
	{
		p0.x = map->coords[i].x;
		p0.y = map->coords[i].y;
		if ((i + 1) % map->width != 0)
		{
			p1.x = map->coords[i + 1].x;
			p1.y = map->coords[i + 1].y;
			draw_line(img, p0, p1, map);
		}
		if (i < map->width * (map->height - 1))
		{
			p1.x = map->coords[i + map->width].x;
			p1.y = map->coords[i + map->width].y;
			draw_line(img, p0, p1, map);
		}
	}
}

void				draw(t_fdf *fdf)
{
	int				i;

	cpy_inp_coords(fdf);
	i = -1;
	while (++i < fdf->map.height * fdf->map.width)
	{
		scale_img(&fdf->map.coords[i].x, &fdf->map.coords[i].y,
											&fdf->map.coords[i].z, &fdf->map);
		rotate_by_x(&fdf->map.coords[i].y, &fdf->map.coords[i].z,
															fdf->map.alpha_x);
		rotate_by_y(&fdf->map.coords[i].x, &fdf->map.coords[i].z,
															fdf->map.alpha_y);
		if (fdf->map.proj_type == ISO)
			iso(&fdf->map.coords[i].x, &fdf->map.coords[i].y,
														fdf->map.coords[i].z);
		find_min_max(&fdf->map.coords[i].x, &fdf->map.coords[i].y, &fdf->map);
	}
	find_offset(&fdf->img, &fdf->map);
	put_2_img(&fdf->img, &fdf->map);
	mlx_put_image_to_window(fdf->win.mlx_ptr, fdf->win.win_ptr, fdf->img.ptr,
																		0, 0);
	print_curr_params(fdf);
}

void				draw_landscape(t_fdf *fdf)
{
	init_map_params(&fdf->map);
	init_win_params(&fdf->win);
	init_img_params(&fdf->img, &fdf->win);
	draw(fdf);
	mlx_hook(fdf->win.win_ptr, 2, 0, handle_key, fdf);
	mlx_loop(fdf->win.mlx_ptr);
}
