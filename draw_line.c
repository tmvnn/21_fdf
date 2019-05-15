/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 21:52:21 by lbellona          #+#    #+#             */
/*   Updated: 2019/05/15 22:05:48 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				draw_point(t_img_params *img, t_point p, t_map *map)
{
	int				i;

	i = p.x + p.y * img->width + img->dxy.x + img->dxy.y;
	if ((p.x + img->dxy.x >= 0) && (p.x + img->dxy.x < img->width) && (i > 0)
											&& (i < img->width * img->height))
		img->data[i] = POINT_COLOR;
}

void				init_dl_params(t_point *delta, t_point *sign, t_point p1,
																	t_point p0)
{
	delta->x = abs(p1.x - p0.x);
	delta->y = abs(p1.y - p0.y);
	sign->x = p0.x < p1.x ? 1 : -1;
	sign->y = p0.y < p1.y ? 1 : -1;
}

void				draw_line(t_img_params *img, t_point p0, t_point p1,
																	t_map *map)
{
	t_point			delta;
	t_point			sign;
	int				error;
	int				error2;

	init_dl_params(&delta, &sign, p1, p0);
	error = delta.x - delta.y;
	draw_point(img, p1, map);
	while (p0.x != p1.x || p0.y != p1.y)
	{
		draw_point(img, p0, map);
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

	if (fdf->map.proj_type == ISO)
		mlx_string_put(fdf->win.mlx_ptr, fdf->win.win_ptr, 5, 5, TEXT_COLOR,
													"Projection type : iso");
	else
		mlx_string_put(fdf->win.mlx_ptr, fdf->win.win_ptr, 5, 5, TEXT_COLOR,
												"Projection type : parallel");
	str = ft_itoa(fdf->map.scale);
	fr_n_re(&str, ft_strjoin("X scale : ", str));
	mlx_string_put(fdf->win.mlx_ptr, fdf->win.win_ptr, 5, 25, TEXT_COLOR, str);
	str[0] = 'Y';
	mlx_string_put(fdf->win.mlx_ptr, fdf->win.win_ptr, 5, 45, TEXT_COLOR, str);
	fr_n_re(&str, ft_itoa(fdf->map.z_scale));
	fr_n_re(&str, ft_strjoin("Z scale : ", str));
	mlx_string_put(fdf->win.mlx_ptr, fdf->win.win_ptr, 5, 65, TEXT_COLOR, str);
	free(str);
}
