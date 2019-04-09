/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:55:47 by lbellona          #+#    #+#             */
/*   Updated: 2019/04/09 22:36:21 by lbellona         ###   ########.fr       */
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
			draw_landscape(coords);
		}
		else
			return ((int)pr_error("map error"));
	}

	return (0);
}
