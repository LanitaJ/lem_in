# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljerk <ljerk@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/31 13:58:04 by ljerk             #+#    #+#              #
#    Updated: 2020/09/13 11:33:10 by ljerk            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRCS := main.c links.c get_rooms.c error_handle.c deadlocks.c
OBJ = $(SRCS:.c=.o)

LIB_DIR = ./ft_printf/
LIBFT = $(LIB_DIR)libftprintf.a

FLAGS = -g -Wall -Werror -Wextra
INCLUDE = ./includes/lemin.h

all: $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $<

$(NAME): $(OBJ)
	$(MAKE) -C $(LIB_DIR)
	gcc -o $(NAME) $(FLAGS) $(OBJ) $(LIBFT)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all