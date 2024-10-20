# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 17:27:32 by yalechin          #+#    #+#              #
#    Updated: 2024/10/19 17:41:29 by yalechin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d 
CFILES = cub3d.c \
			minimap.c \
			map_parsing.c \
			error.c \
			map_setting_utils.c \
			movement.c \
			ray_casting.c \
			exit.c \
			ft_utils.c \
			render_wall.c
OFILES = $(CFILES:.c=.o)

FLAGS = -O3 -Wall -Wextra -Werror -g
MLX_PATH = MLX42/build/
LIBFT = libft
LIBFT_FLAGS = -L$(LIBFT) -lft

MLX_FLAGS = -L$(MLX_PATH) -lmlx42 -lglfw -lGL -lXext -lX11 -lm 


all: lib $(NAME) 

lib:
#@make -C $(MLX_PATH)
	@make -C $(LIBFT)


$(NAME): $(OFILES)
	cc $(FLAGS) $^ $(LIBFT_FLAGS) -L$(MLX_PATH) $(MLX_FLAGS) -o $(NAME) 

%.o: %.c libft/get_next_line.h libft/libft.h
	cc $(FLAGS) -c $< -o $@

clean: 
	rm -f $(OFILES)
	@make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: clean fclean all re lib