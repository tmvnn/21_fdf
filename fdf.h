/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 20:42:16 by lbellona          #+#    #+#             */
/*   Updated: 2019/05/04 00:36:56 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <fcntl.h>
# include "mlx.h"
# include <math.h>
# include <errno.h>
# include "get_next_line.h"

# define ABS(number) ((number) > 0 ? (number):-(number))
# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000
# define MAP_SCALE 25

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
}					t_point;

typedef struct      s_win_params
{
    void			*mlx_ptr;
    void			*win_ptr;
	int				width;
	int				height;
	int				color;
 }                  t_win_params;

typedef struct      s_img_params                                                                       {
	int				*ptr;
	int				*data;
	int				bpp;
	int				size_l;
	int				endian;
	int				width;
	int				height;
}					t_img_params;

typedef struct				s_3d_coords
{
	int						x;
	int						y;
	int						z;
	struct s_3d_coords		*next;
}							t_3d_coords;

typedef struct				s_map
{
	t_point					min;
	t_point					max;
	int						scale;
	t_point                 *inp_coords;
	t_point					*coords;
	int						width;
	int						height;
	float					alpha_x;
	float					alpha_y;
}							t_map;

typedef struct				s_fdf
{
	t_map					map;
	t_win_params			win;
	t_img_params			img;
}							t_fdf;

int					pr_exit(int key, t_fdf *fdf);
void				draw_line(t_img_params *img, t_point p0, t_point p1, t_map *map);
void                draw_landscape(t_fdf *fdf);
void				ft_print_map(t_fdf *fdf);
void				rotate_by_x1(t_map *map);
void				clean_img(t_img_params *img);
void				draw(t_fdf *fdf);
//void				draw_line(t_win_params p, t_point p0, t_point p1);

#endif
