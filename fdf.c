/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:55:47 by lbellona          #+#    #+#             */
/*   Updated: 2019/05/15 21:19:04 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				*pr_error(char *err_msg)
{
	perror(err_msg);
	exit(1);
}

void				check_map_width(t_map *map)
{
	static int		old_width;

	if (map->height == 1)
		old_width = map->width;
	else if (old_width != map->width)
		pr_error("wrong map width");
}

int					read_map(int fd, t_fdf *fdf)
{
	char			*line;
	int				i;
	t_3d_coords		*coords_lst;

	i = 0;
	fdf->map.avg_z = 0;
	coords_lst = 0;
	fdf->map.height = 0;
	while ((i = get_next_line(fd, &line)) > 0)
	{
		(*line == 0) ? pr_error("wrong line from file") : (void*)0;
		if (!(get_3d_coords(line, &coords_lst, fdf)))
			return (0);
		check_map_width(&fdf->map);
	}
	close(fd);
	free(line);
	if (!(fdf->map.coords = (t_point*)malloc(sizeof(t_point) * fdf->map.height
															* fdf->map.width))
			|| !(fdf->map.inp_coords = (t_point*)malloc(sizeof(t_point) *
											fdf->map.height * fdf->map.width)))
		pr_error("memory allocation error");
	put_coords_2_arr(coords_lst, fdf);
	clear_coords_lst(&coords_lst);
	return (1);
}

int					main(int argc, char **argv)
{
	int				fd;
	t_fdf			fdf;

	errno = 0;
	if (argc != 2)
		ft_putstr("Usage : ./fdf <filename>\n");
	else
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			return ((int)pr_error(""));
		if (read_map(fd, &fdf))
			draw_landscape(&fdf);
		else
			return ((int)pr_error("map error"));
	}
	return (0);
}
