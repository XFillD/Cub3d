# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/20 11:40:36 by yalechin          #+#    #+#              #
#    Updated: 2024/10/13 14:16:31 by yalechin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a


CFILES = ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_printf.c \
			ft_print_char.c \
			ft_print_numbers.c \
			ft_print_strings.c \
			ft_print_hex_l.c \
			ft_print_hex_u.c \
			ft_print_unsigned.c \
			ft_print_pointer.c \
			get_next_line.c \
			get_next_line_utils.c

		
OFILES = $(CFILES:.c=.o)  

CC = gcc
HDRS = libft.h
CFLAGS = -Wall -Wextra -Werror


all: $(NAME) 

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)


clean:
	rm -f $(OFILES) 


fclean: clean 
	rm -f $(NAME)


re: fclean all 
