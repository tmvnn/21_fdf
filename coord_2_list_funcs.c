/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_2_list_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timuryakubov <timuryakubov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:29:07 by lbellona          #+#    #+#             */
/*   Updated: 2019/10/01 18:04:10 by timuryakubo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void				ft_list_push_back(t_3d_coords **begin_list,
														t_3d_coords *cur_elem)
{
	t_3d_coords		*tmpptr;

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

int					add_coords_2_lst(t_3d_coords **coords,
									char *line, t_fdf *fdf, int delta)
{
	t_3d_coords		*cur_elem;
	int				z;

	z = ft_atoi(line + delta);
	fdf->map.avg_z += z;
	if (!(cur_elem = ft_create_lst_elem(fdf->map.width - 1,
								fdf->map.height - 1, z)))
	{
		clear_coords_lst(coords);
		pr_error("memory allocation error");
		return (0);
	}
	ft_list_push_back(coords, cur_elem);
	return (1);
}

void				put_coords_2_arr(t_3d_coords *coords_lst, t_fdf *fdf)
{
	int				i;

	fdf->map.min.x = INT_MAX;
	fdf->map.max.x = -INT_MIN;
	fdf->map.min.y = INT_MAX;
	fdf->map.max.y = -INT_MIN;
	fdf->map.avg_z /= (fdf->map.height * fdf->map.width);
	i = 0;
	while (coords_lst)
	{
		fdf->map.inp_coords[i].x = coords_lst->x;
		fdf->map.inp_coords[i].y = coords_lst->y;
		find_min_max(&fdf->map.inp_coords[i].x, &fdf->map.inp_coords[i].y,
																	&fdf->map);
		fdf->map.inp_coords[i++].z = coords_lst->z - fdf->map.avg_z;
		coords_lst = coords_lst->next;
	}
}

void				clear_coords_lst(t_3d_coords **coords_lst)
{
	t_3d_coords *elem;
	t_3d_coords *tmp;

	elem = *coords_lst;
	if (!elem)
		return ;
	while (elem)
	{
		tmp = elem->next;
		free(elem);
		elem = tmp;
	}
	*coords_lst = 0;
}
