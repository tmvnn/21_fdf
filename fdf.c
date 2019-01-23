/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 20:10:35 by lbellona          #+#    #+#             */
/*   Updated: 2019/01/23 23:22:00 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			*pr_error(void)
{
	ft_putstr("error\n");
	//ft_putstr("Found wrong line length. Exiting."\n");
	exit(0);
}

int				main(int argc, char **argv)
{
	int			fd;
	void		*mlx_ptr;
	void		*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "tets_win");
	mlx_pixel_put(mlx_ptr, win_ptr, 5, 5, 0xFFFFFF);
	//mlx_string_put(mlx_ptr, win_ptr, 5, 5, 0xFFFFFF, "asdasdasd");
	mlx_loop(mlx_ptr);

	//if (argc != 2)
	//	ft_putstr("Usage : ./fdf <filename> [ case_size z_size ]\n");
	//else
	{
	//	if ((fd = open(argv[1], O_RDONLY)) < 0)
	//		return ((int)pr_error());
		/*
		if ((tets = read_2_lst(fd, &tet_num)))
		{
			if (connetivity_is_valid(tets, tet_num))
				solve_map(tets, tet_num);
		}
		else
			return ((int)pr_error());
		*/
	}

	return (0);
}
