# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/15 15:43:55 by abiru             #+#    #+#              #
#    Updated: 2023/01/19 16:13:07 by abiru            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = cc

CFLAGS = -Wextra -Werror -Wall

SRCS = loop.c fractol_utils.c

OBJS = $(SRCS:.c=.o)

MLX_DIR = mlx

all: $(NAME)

%.o: %.c
	$(CC) -Imlx -c $< -o $@

$(NAME): $(OBJS)
	@cd mlx && make
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	@cd mlx && make clean
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re