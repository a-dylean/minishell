NAME = minishell

CC = cc -g
# for debugging -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I includes -I libft

SRC = 	src/main.c src/terminal.c src/init.c src/env_utils.c src/test.c \
        src/utils/array.c src/utils/linked_lists.c src/utils/string.c \
        src/errors/printer_utils.c src/errors/syntax.c \
        src/executer/builtins.c src/executer/executer.c src/executer/ft_exit.c src/executer/ft_cd.c src/executer/ft_echo.c\
        src/expander/buffer.c src/expander/env.c src/expander/expander.c \
        src/lexer/lexer.c src/lexer/types.c \
        src/parser/cmds_ops.c src/parser/parser.c src/parser/redirections_ops.c src/parser/tokens_ops.c \

OBJ_DIR = obj
OBJ := $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRC))

LIBFT = libft/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

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