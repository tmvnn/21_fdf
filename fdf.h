/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 20:42:16 by lbellona          #+#    #+#             */
/*   Updated: 2019/02/18 00:07:32 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define BUFF_SIZE 21
# define TET_SIZE 4

# include "libft.h"
# include <fcntl.h>
# include "mlx.h"

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

typedef struct      s_draw_params
{
     void			*mlx_ptr;
     void			*win_ptr;
	 int			win_width;
	 int			win_height;
	 int			color;
 }                   t_draw_params;

//void				*pr_error();
//int					input_is_valid(char *buff);

#endif
