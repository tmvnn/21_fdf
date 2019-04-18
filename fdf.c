/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:55:47 by lbellona          #+#    #+#             */
/*   Updated: 2019/04/19 00:17:58 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int					pr_exit(int key, t_map *map)
{
	if (key == 53)
		exit(0);
	if (key == 125)
		draw_landscape(map);
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
									char *line, t_map *map, int delta)
{
	t_3d_coords     *cur_elem;

	if (!(cur_elem = ft_create_lst_elem(map->width - 1,
								map->height - 1, ft_atoi(line + delta))))
	{
		//free allocated memery
		return (0);
	}
	ft_list_push_back(coords, cur_elem);
	return (1);
}

int					get_3d_coords(char *line, t_3d_coords **coords,
															t_map *map)
{
	int				i;
	int				delta;

	i = -1;
	delta = 0;
	map->width = 0;
	while (line[++i])
	{
		if ((line[i] >= '0' && line[i] <='9') || line[i] == '-')
		{
			delta = i;
			map->width++;
			while ((line[i] >= '0' && line[i] <='9') || line[i] == '-')
				i++;
			if (!line[i])
				i--;
			else
				line[i] = 0;
			if (!(add_coords_2_lst(coords, line, map, delta)))
				return (0);
			//printf("%d ", ft_atoi(line + delta));
		}
	}
	return (1);
}

void				put_coords_2_arr(t_3d_coords *coords_lst, t_map *map)
{
	int 			i;

	i = 0;
	while (coords_lst)
	{
		map->coords[i].x = coords_lst->x;
		map->coords[i].y = coords_lst->y;
		map->coords[i++].z = coords_lst->z;
		coords_lst = coords_lst->next;
	}
}

void				ft_print_map(t_map *map)
{
	int 			i;

	i = -1;
	while (++i < map->height * map->width)
	{
		printf("%d ", map->coords[i].x);
		if ((i + 1) % map->width == 0)
			printf("\n");
	}
	printf("\n");
	i = -1;
	while (++i < map->height * map->width)
	{
		printf("%d ", map->coords[i].y);
		if ((i + 1) % map->width == 0)
			printf("\n");
	}
	printf("\n");
}

int					read_map(int fd, t_map *map)
{
	char 			*line;
	int				i;
	t_3d_coords		*coords_lst;

	i = 0;
	coords_lst = 0;
	map->height = 0;
	while ((i = get_next_line(fd, &line)) > 0)
	{
		map->height++;
		if(!(get_3d_coords(line, &coords_lst, map)))
			return (0);
	}
	close(fd);
	if (!(map->coords = (t_point*)malloc(sizeof(t_point) * map->height
															* map->width)))
		pr_error("memory allocation error");
	put_coords_2_arr(coords_lst, map);
	ft_print_map(map);
	return (1);
}

int					main(int argc, char **argv)
{
	int				fd;
	t_map		map;

	errno = 0;
	if (argc != 3)
		ft_putstr("Usage : ./fdf <filename> <projection_type_1_or_2>\n");
	else
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			return ((int)pr_error(""));
		if (read_map(fd, &map))
		{
			//ft_print_lst(coords_lst, &map);
			//printf("%d\n", map_size.height);
			draw_landscape(&map);
		}
		else
			return ((int)pr_error("map error"));
	}
	return (0);
}
