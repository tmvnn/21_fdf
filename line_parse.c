/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 20:11:07 by lbellona          #+#    #+#             */
/*   Updated: 2019/05/15 22:10:14 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int					is_correct_char(char c)
{
	if ((c < '0' || c > '9') && (c < 8 || c > 13) && c != ' '
			&& c != '-' && c != '+')
	{
		pr_error("Wrong char");
		return (0);
	}
	return (1);
}

int					get_3d_coords(char *line, t_3d_coords **coords, t_fdf *fdf)
{
	int				i;
	int				delta;

	i = -1;
	delta = 0;
	fdf->map.width = 0;
	fdf->map.height++;
	while (line[++i])
	{
		is_correct_char(line[i]);
		if ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
		{
			delta = i;
			fdf->map.width++;
			while ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
				i++;
			if (!line[i])
				i--;
			else if (is_correct_char(line[i]))
				line[i] = 0;
			add_coords_2_lst(coords, line, fdf, delta);
		}
	}
	free(line);
	return ((*coords == 0) ? 0 : 1);
}
