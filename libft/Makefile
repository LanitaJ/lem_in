
# program name
NAME = libft.a

# compilation flags
FLAGS = -Wall -Wextra -Werror -c

# function names without .c
FUNC = ft_lstnew ft_lstdelone ft_lstdel ft_lstadd ft_lstiter ft_lstmap \
	ft_putchar ft_putstr ft_atoi ft_memset ft_bzero ft_memcpy ft_memmove \
	ft_memccpy ft_memchr ft_memcmp ft_strlen ft_strdup ft_strcpy ft_strcat \
	ft_strncat ft_strlcat ft_strchr ft_strrchr ft_strstr ft_strnstr ft_strcmp \
	ft_strncmp ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
	ft_tolower ft_toupper ft_strncpy ft_memalloc ft_memdel ft_strnew \
	ft_strdel ft_strclr ft_striter ft_striteri ft_strmap ft_strmapi ft_strequ \
	ft_strnequ ft_strsub ft_strjoin ft_putnbr ft_itoa ft_strtrim ft_putendl \
	ft_strsplit ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd

# my functions without .c
MY_FUNC = ft_mylengthofnum ft_myswap ft_fillmynbr ft_my_counting_of_str \
		ft_my_count_c_words ft_my_malloc_c_word ft_my_printlist \
		ft_mydltlst get_next_line

# functions with .c
FUNC_C = $(patsubst %, %.c, $(FUNC))

# my functions with .c
MY_FUNC_C = $(patsubst %, %.c, $(MY_FUNC))

# header brrruh .h
HEADERS = libft.h

# object files .o
FUNC_O = $(patsubst %, %.o, $(FUNC))

# object files of my shit .o
MY_FUNC_O = $(patsubst %, %.o, $(MY_FUNC))

# $< - prerekvisit=source && $? - more new prerekvisits

all: $(NAME)

$(NAME): $(FUNC_O) $(MY_FUNC_O) $(HEADERS)
	ar rc $(NAME) $?
	ranlib $(NAME)

$(FUNC_O) $(MY_FUNC_O): %.o: %.c
	gcc $(FLAGS) $? -I $(HEADERS)

clean:
	rm -f $(FUNC_O) $(MY_FUNC_O)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:all clean fclean re
