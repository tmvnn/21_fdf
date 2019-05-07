/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_landscape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:55:36 by lbellona          #+#    #+#             */
/*   Updated: 2019/05/07 23:26:32 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void				draw_line(t_img_params *img, t_point p0, t_point p1, t_map *map)
{
	t_point			delta;
	t_point			sign;
	int				error;
	t_point			dxy;
	int				dx;
	int 			error2;

	dxy.x = abs(map->min.x) + (img->width - abs(map->max.x - map->min.x)) / 2 + map->x_offset;
	dxy.y = (abs(map->min.y) + (img->height - abs(map->max.y - map->min.y)) / 2 + map->y_offset) * img->width;
	delta.x = abs(p1.x - p0.x);
	delta.y = abs(p1.y - p0.y);
	sign.x = p0.x < p1.x ? 1 : -1;
	sign.y = p0.y < p1.y ? 1 : -1;
	error = delta.x - delta.y;
	if ((p1.x + dxy.x >= 0) && (p1.x + dxy.x < img->width) &&
			(p1.x + p1.y * img->width + dxy.x + dxy.y > 0) &&
			(p1.x + p1.y * img->width + dxy.x + dxy.y < img->width * img->height))
		img->data[p1.x + p1.y * img->width + dxy.x + dxy.y] = 0xFFFFFF;
	while (p0.x != p1.x || p0.y != p1.y)
	{
		if ((p0.x + dxy.x >= 0) && (p0.x + dxy.x < img->width) &&
				(p0.x + p0.y * img->width + dxy.x + dxy.y > 0) &&
				(p0.x + p0.y * img->width + dxy.x + dxy.y < img->width * img->height))
			img->data[p0.x + p0.y * img->width + dxy.x + dxy.y] = 0xFFFFFF;
		error2 = error * 2;
		if ((error2) > (-delta.y))
		{
			error -= delta.y;
			p0.x += sign.x;
		}
		if ((error2) < (delta.x))
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

int					auto_map_scale(t_map *map)
{
	int				scale;

	scale = 1;
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

static int			fr_n_re(char **oldstr, char *newstr)
{
	char			*tmp;

	tmp = *oldstr;
	if (!newstr)
		return (0);
	*oldstr = newstr;
		free(tmp);
	return (1);
}

void				print_curr_params(t_fdf *fdf)
{
	char			*str;
	char			*tmp;

	if (fdf->map.proj_type == ISO)
		mlx_string_put(fdf->win.mlx_ptr, fdf->win.win_ptr, 5, 5, 0xFFFFFF,
													"Projection type : iso");
	else
		mlx_string_put(fdf->win.mlx_ptr, fdf->win.win_ptr, 5, 5, 0xFFFFFF,
												"Projection type : parallel");
	str = ft_itoa(fdf->map.scale);
	fr_n_re(&str, ft_strjoin("X scale : ", str));
	mlx_string_put(fdf->win.mlx_ptr, fdf->win.win_ptr, 5, 25, 0xFFFFFF, str);
	str[0] = 'Y';
	mlx_string_put(fdf->win.mlx_ptr, fdf->win.win_ptr, 5, 45, 0xFFFFFF, str);
	fr_n_re(&str, ft_itoa(fdf->map.z_scale));
	fr_n_re(&str, ft_strjoin("Z scale : ", str));
	mlx_string_put(fdf->win.mlx_ptr, fdf->win.win_ptr, 5, 65, 0xFFFFFF, str);
	free(str);
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
	//al += 0.1;
}

void				find_min_max(int *x, int *y, t_map *map)
{
	if (map->min.x > *x)
		map->min.x = *x;
	if (map->min.y > *y)
		map->min.y = *y;
	if (map->max.x < *x)
		map->max.x = *x;
	if (map->max.y < *y)
		map->max.y = *y;
}

void cpy_inp_coords(t_fdf *fdf)
{
	int i;

	fdf->map.min.x = 999999999;
	fdf->map.max.x = 0;
	fdf->map.min.y = 999999999;
	fdf->map.max.y = 0;
	i = -1;
	while (++i < fdf->map.height * fdf->map.width)
	{
		fdf->map.coords[i].x = fdf->map.inp_coords[i].x;
		fdf->map.coords[i].y = fdf->map.inp_coords[i].y;
		fdf->map.coords[i].z = fdf->map.inp_coords[i].z;
	}
}

void				draw(t_fdf *fdf)
{
	int				i;

	cpy_inp_coords(fdf);
	i = -1;
	while (++i < fdf->map.height * fdf->map.width)
	{
		scale_img(&fdf->map.coords[i].x, &fdf->map.coords[i].y, &fdf->map.coords[i].z, &fdf->map);
		rotate_by_x(&fdf->map.coords[i].y, &fdf->map.coords[i].z, fdf->map.alpha_x);
		rotate_by_y(&fdf->map.coords[i].x, &fdf->map.coords[i].z, fdf->map.alpha_y);
		if (fdf->map.proj_type == ISO)
			iso(&fdf->map.coords[i].x, &fdf->map.coords[i].y, fdf->map.coords[i].z);
		find_min_max(&fdf->map.coords[i].x, &fdf->map.coords[i].y, &fdf->map);
	}
	put_2_img(&fdf->img, &fdf->map);
	mlx_put_image_to_window(fdf->win.mlx_ptr, fdf->win.win_ptr, fdf->img.ptr, 0, 0);
	print_curr_params(fdf);
	//printf("al_x = %f\n", fdf->map.alpha_x);
	//printf("al_y = %f\n", fdf->map.alpha_y);
	//printf("\n");
}

void				draw_landscape(t_fdf *fdf)
{
	init_map_params(&fdf->map);
	init_win_params(&fdf->win);
	init_img_params(&fdf->img, &fdf->win);

	draw(fdf);

	//ft_print_map(fdf);
	//put_2_img(&fdf->img, &fdf->map);

	/*t_point p0, p1;
	p0.x = 1;
	p0.y = 1;
	p1.x = 25;
	p1.y = 15;
	draw_line(&fdf->img, p0, p1, &fdf->map);*/

	//mlx_put_image_to_window(fdf->win.mlx_ptr, fdf->win.win_ptr, fdf->img.ptr, 0, 0);

	//clean_img(&img);
	//mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, img.ptr, 0, 0);

	//mlx_key_hook(win.win_ptr, pr_exit, (void *)0);

	mlx_hook(fdf->win.win_ptr, 2, 0, do_action, fdf);
	mlx_loop(fdf->win.mlx_ptr);
}
