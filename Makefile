NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes -I libft
SRC = src/main.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) -L libft -lft

$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re