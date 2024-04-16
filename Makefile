NAME = minishell

CC = cc -g
# for debugging -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I includes -I libft

SRC = src/main.c src/terminal.c src/lexer.c src/linked_lists.c src/errors.c src/parser_errors.c \
	  src/parser.c src/parser_cmds_ops.c src/parser_redirections_ops.c src/parser_tokens_ops.c \
	  src/test.c src/expander.c src/utils_array.c src/utils_str.c

OBJ_DIR = obj
OBJ := $(patsubst src/%.c,obj/%.o,$(SRC))

LIBFT = libft/libft.a

all: $(NAME)

obj/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) -L libft -lft -lreadline

$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re