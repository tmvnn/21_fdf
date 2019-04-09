/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 20:42:16 by lbellona          #+#    #+#             */
/*   Updated: 2019/04/09 22:31:41 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define TET_SIZE 4

# include "libft.h"
# include <fcntl.h>
# include "mlx.h"
# include <math.h>
# include <errno.h>
# include "get_next_line.h"

# define ABS(number) ((number) > 0 ? (number):-(number))

typedef struct		s_tetlst
{
	char			x[TET_SIZE];
	char			y[TET_SIZE];
	char			letter;
	struct s_tetlst *next;
}					t_tetlst;

typedef struct		s_point
{
	int				x;
	int				y;
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

typedef struct				s_3d_size
{
	int						width;
	int						height;
}							t_3d_size;

int					pr_exit(int key);
void				draw_line(t_img_params *img, t_point p0, t_point p1);
void                draw_landscape(t_3d_coords *coords);
//void				draw_line(t_win_params p, t_point p0, t_point p1);

#endif
