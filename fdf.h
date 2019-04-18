/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 20:42:16 by lbellona          #+#    #+#             */
/*   Updated: 2019/04/19 00:17:56 by lbellona         ###   ########.fr       */
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
# define MAP_SCALE 30

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
	t_point					*coords;
	int						width;
	int						height;
}							t_map;

int					pr_exit(int key, t_map *map);
void				draw_line(t_img_params *img, t_point p0, t_point p1, t_map *map);
void                draw_landscape(t_map *map);
void				ft_print_map(t_map *map);
void				rotate_by_x(t_map *map);
//void				draw_line(t_win_params p, t_point p0, t_point p1);

#endif
