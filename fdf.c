/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:55:47 by lbellona          #+#    #+#             */
/*   Updated: 2019/05/07 23:26:39 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int					do_action(int key, t_fdf *fdf)
{
	if (key == 53)
		exit(0);
	if (key == 84)
		fdf->map.alpha_x += 0.1;
	if (key == 87)
		fdf->map.alpha_x -= 0.1;
	if (key == 83)
		fdf->map.alpha_y -= 0.1;
	if (key == 85)
		fdf->map.alpha_y += 0.1;
	if (key == 69)
		fdf->map.scale += 1;
	if (key == 78 && fdf->map.scale > 0)
		fdf->map.scale -= 1;
	if (key == 27 && fdf->map.z_scale > 0)
		fdf->map.z_scale -= 1;
	if (key == 24)
		fdf->map.z_scale += 1;
	if (key == 123)
		fdf->map.x_offset -= 10;
	if (key == 124)
		fdf->map.x_offset += 10;
	if (key == 126)
		fdf->map.y_offset -= 10;
	if (key == 125)
		fdf->map.y_offset += 10;
	if (key == 35)
		fdf->map.proj_type *= -1;
	clean_img(&fdf->img);
	draw(fdf);
	return (0);
}

void				*pr_error(char *err_msg)
{
					perror(err_msg);
					exit(1);
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

void				ft_print_lst(t_3d_coords *coords, t_map *map)
{
	int 			i;

	i = 1;
	while (coords)
	{
		printf("%d ", coords->y);
		if (i % map->width == 0)
			printf("\n");
		i++;
		coords = coords->next;
	}
}

int					add_coords_2_lst(t_3d_coords **coords,
									char *line, t_fdf *fdf, int delta)
{
	t_3d_coords     *cur_elem;

	if (!(cur_elem = ft_create_lst_elem(fdf->map.width - 1,
								fdf->map.height - 1, ft_atoi(line + delta))))
	{
		//free allocated memery
		return (0);
	}
	ft_list_push_back(coords, cur_elem);
	return (1);
}

int					get_3d_coords(char *line, t_3d_coords **coords, t_fdf *fdf)
{
	int				i;
	int				delta;

	i = -1;
	delta = 0;
	fdf->map.width = 0;
	while (line[++i])
	{
		if ((line[i] >= '0' && line[i] <='9') || line[i] == '-')
		{
			delta = i;
			fdf->map.width++;
			while ((line[i] >= '0' && line[i] <='9') || line[i] == '-')
				i++;
			if (!line[i])
				i--;
			else
				line[i] = 0;
			if (!(add_coords_2_lst(coords, line, fdf, delta)))
				return (0);
			//printf("%d ", ft_atoi(line + delta));
		}
	}
	return (1);
}

void				put_coords_2_arr(t_3d_coords *coords_lst, t_fdf *fdf)
{
	int 			i;

	fdf->map.min.x = 999999999;
	fdf->map.max.x = 0;
	fdf->map.min.y = 999999999;
	fdf->map.max.y = 0;
	i = 0;
	while (coords_lst)
	{
		fdf->map.inp_coords[i].x = coords_lst->x;
		fdf->map.inp_coords[i].y = coords_lst->y;
		find_min_max(&fdf->map.inp_coords[i].x, &fdf->map.inp_coords[i].y, &fdf->map);
		fdf->map.inp_coords[i++].z = coords_lst->z;
		coords_lst = coords_lst->next;
	}
}

void				ft_print_map(t_fdf *fdf)
{
	int 			i;

	i = -1;
	while (++i < fdf->map.height * fdf->map.width)
	{
		printf("%d ", fdf->map.inp_coords[i].x);
		if ((i + 1) % fdf->map.width == 0)
			printf("\n");
	}
	printf("\n");
	i = -1;
	while (++i < fdf->map.height * fdf->map.width)
	{
		printf("%d ", fdf->map.inp_coords[i].y);
		if ((i + 1) % fdf->map.width == 0)
			printf("\n");
	}
	printf("\n");
}

void				clear_coords_lst(t_3d_coords **coords_lst)
{
	t_3d_coords *elem;
	t_3d_coords *tmp;

	elem = *coords_lst;
	if (!elem)
		return;
	while (elem)
	{
		tmp = elem;
		free(elem);
		elem = tmp->next;
	}
	*coords_lst = 0;
}

int					read_map(int fd, t_fdf *fdf)
{
	char 			*line;
	int				i;
	t_3d_coords		*coords_lst;

	i = 0;
	coords_lst = 0;
	fdf->map.height = 0;
	while ((i = get_next_line(fd, &line)) > 0)
	{
		fdf->map.height++;
		if(!(get_3d_coords(line, &coords_lst, fdf)))
			return (0);
		free(line);
	}
	close(fd);
	if (!(fdf->map.coords = (t_point*)malloc(sizeof(t_point) * fdf->map.height
															* fdf->map.width)))
		pr_error("memory allocation error");
	if (!(fdf->map.inp_coords = (t_point*)malloc(sizeof(t_point) *
											fdf->map.height * fdf->map.width)))
		pr_error("memory allocation error");
	put_coords_2_arr(coords_lst, fdf);
	clear_coords_lst(&coords_lst);
	//ft_print_map(fdf);
	return (1);
}

int					main(int argc, char **argv)
{
	int				fd;
	t_fdf		fdf;

	errno = 0;
	if (argc != 2)
		ft_putstr("Usage : ./fdf <filename>\n");
	else
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			return ((int)pr_error(""));
		if (read_map(fd, &fdf))
		{
			//ft_print_lst(coords_lst, &map);
			//printf("height = %d\n", fdf.map.height);
			//printf("width = %d\n", fdf.map.width);
			draw_landscape(&fdf);
		}
		else
			return ((int)pr_error("map error"));
	}
	return (0);
}
