/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 20:10:35 by lbellona          #+#    #+#             */
/*   Updated: 2019/04/08 22:45:21 by lbellona         ###   ########.fr       */
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

void				*pr_error(char *err_msg)
{
					perror(err_msg);
					exit(0);
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

t_3d_coords			*ft_create_lst_elem(int x, int y, int z)
{
	t_3d_coords		*new_elem;

	if ((new_elem = (t_3d_coords*)malloc(sizeof(t_3d_coords))))
	{
		new_elem->next = 0;
		new_elem->x = x;
		new_elem->y = y;
		new_elem->z = z;
	}
	else
		pr_error("memory allocation error");
	return (new_elem);
}

void            	ft_list_push_back(t_3d_coords **begin_list, t_3d_coords *cur_elem)
{
	t_3d_coords 	*tmpptr;

	if (!(*begin_list))
		*begin_list = cur_elem;
	else
	{
		tmpptr = *begin_list;
		while (tmpptr->next)
			tmpptr = tmpptr->next;
		tmpptr->next = cur_elem;
	}
}

void				ft_print_lst(t_3d_coords *coords)
{
	while (coords)
	{
		printf("%d ", coords->z);
		coords = coords->next;
	}
}

int					add_coords_2_lst(t_3d_coords **coords,
									char *line, t_3d_size *map_size, int delta)
{
	t_3d_coords     *cur_elem;

	if (!(cur_elem = ft_create_lst_elem(map_size->width - 1,
								map_size->height - 1, ft_atoi(line + delta))))
	{
		//free allocated memery
		return (0);
	}
	ft_list_push_back(coords, cur_elem);
	return (1);
}

int					get_3d_coords(char *line, t_3d_coords **coords,
															t_3d_size *map_size)
{
	int				i;
	int				delta;

	i = -1;
	delta = 0;
	map_size->width = 0;
	while (line[++i])
	{

		if ((line[i] >= '0' && line[i] <='9') || line[i] == '-')
		{
			delta = i;
			map_size->width++;
			while ((line[i] >= '0' && line[i] <='9') || line[i] == '-')
				i++;
			if (!line[i])
				i--;
			else
				line[i] = 0;
			if (!(add_coords_2_lst(coords, line, map_size, delta)))
				return (0);
			printf("%d ", ft_atoi(line + delta));
		}
	}
	return (1);
}

t_3d_coords			*read_map(int fd, t_3d_size *map_size)
{
	char 			*line;
	int				i;
	t_3d_coords		*coords;

	i = 0;
	coords = 0;
	map_size->height = 0;
	while ((i = get_next_line(fd, &line)) > 0)
	{
		map_size->height++;
		if(!(get_3d_coords(line, &coords, map_size)))
			return (0);
		printf("\n");
	}
	printf("\n");
	close(fd);
	return (coords);
}

int					main(int argc, char **argv)
{
	int				fd;
	t_3d_coords		*coords;
	t_3d_size		map_size;

	errno = 0;
	if (argc != 3)
		ft_putstr("Usage : ./fdf <filename> <projection_type_1_or_2>\n");
	else
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			return ((int)pr_error(""));
		if ((coords = read_map(fd, &map_size)))
		{
			ft_print_lst(coords);
			//printf("%d\n", map_size.height);
			//draw_landscape(&coords);
		}
		else
			return ((int)pr_error("map error"));
	}

	return (0);
}
