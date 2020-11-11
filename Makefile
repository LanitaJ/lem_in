# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: icanker <icanker@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/31 13:58:04 by ljerk             #+#    #+#              #
#    Updated: 2020/11/10 15:09:35 by icanker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRCS := main.c links.c get_rooms.c error_handle.c deadlocks.c bfs.c \
		choose_type.c do_types.c checkmap.c bonus.c print_solve.c \
		solve_service.c free_all.c get_rooms2.c init.c links2.c \
		error_handle2.c solve_service2.c
OBJ = $(SRCS:.c=.o)

LIB_DIR = ./ft_printf/
LIBFT = $(LIB_DIR)libftprintf.a

FLAGS = -g -Wall -Werror -Wextra
INCLUDE = ./includes/lemin.h

all: $(NAME)

%.o: %.c $(INCLUDE)
	gcc $(FLAGS) -c $<

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