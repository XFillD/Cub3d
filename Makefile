# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhauba <fhauba@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 17:27:32 by yalechin          #+#    #+#              #
#    Updated: 2024/11/17 14:10:32 by fhauba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d 
CFILES = srcs/cub3d.c \
			srcs/minimap.c \
			srcs/map_parsing.c \
			srcs/error.c \
			srcs/map_setting_utils.c \
			srcs/movement.c \
			srcs/ray_casting.c \
			srcs/exit.c \
			srcs/ft_utils.c \
			srcs/render_wall.c \
			srcs/map_check.c \
			srcs/map_check2.c \
			srcs/render.c \
			srcs/render_other.c \
			srcs/ray_utils.c \
			srcs/line_utils.c \
			srcs/cleanup.c \
			srcs/buffer_utils.c
OFILES = $(CFILES:.c=.o)

FLAGS = -O3 -Wall -Wextra -Werror -g
MLX_PATH = MLX42/build/
LIBFT = libft
LIBFT_FLAGS = -L$(LIBFT) -lft

MLX_FLAGS = -L$(MLX_PATH) -lmlx42 -lglfw -lGL -lXext -lX11 -lm 


all: lib $(NAME) 

lib:
	@make -C $(MLX_PATH)
	@make -C $(LIBFT)


$(NAME): $(OFILES)
	cc $(FLAGS) $^ $(LIBFT_FLAGS) -L$(MLX_PATH) $(MLX_FLAGS) -o $(NAME) 

%.o: %.c libft/get_next_line.h libft/libft.h
	cc $(FLAGS) -c $< -o $@

clean: 
	rm -f $(OFILES)
	@make clean -C $(LIBFT)
	@make clean -C $(MLX_PATH)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@make clean -C $(MLX_PATH)

re: fclean all

.PHONY: clean fclean all re lib