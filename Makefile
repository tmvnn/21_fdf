# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timuryakubov <timuryakubov@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/24 16:32:39 by lbellona          #+#    #+#              #
#    Updated: 2019/10/01 21:15:47 by timuryakubo      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = fdf.c\
		  coord_2_list_funcs.c\
		  coords_transform.c\
		  draw_landscape.c\
		  draw_line.c\
		  init_start_params.c\
		  line_parse.c

NAME = fdf
WWW = -Wall -Wextra -Werror
INCLUDES = fdf.h

all: $(NAME)

$(NAME):
	make -C ./libft/
	cc -I ./libft/ -L libft -lft -I ./get_next_line/ -I /usr/local/include $(SOURCES) ./get_next_line/get_next_line.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	make -C ./libft/ clean

fclean: clean
	make -C ./libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all
