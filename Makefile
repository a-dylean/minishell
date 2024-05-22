NAME = minishell

CC = cc -g 
# for debugging -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I includes -I libft

SRC = 	src/main.c src/terminal.c src/init.c src/test.c \
		src/builtins/ft_pwd.c src/builtins/ft_cd.c src/builtins/ft_echo.c src/builtins/ft_exit.c src/builtins/ft_env.c\
		src/builtins/ft_export.c src/builtins/ft_unset.c\
        src/utils/array.c src/utils/linked_lists.c src/utils/string.c src/utils/cleanup.c src/utils/write.c\
        src/errors/printer_utils.c src/errors/syntax.c \
        src/executer/executer.c src/executer/redirections.c src/executer/exec_utils.c src/executer/heredoc.c src/executer/open_fds.c\
        src/executer/get_command.c src/executer/redirections_utils.c\
		src/expander/expander.c src/expander/expander_utils.c src/expander/quotes_removal.c \
        src/lexer/lexer.c src/lexer/types.c \
        src/parser/cmds_ops.c src/parser/parser.c src/parser/redirections_ops.c src/parser/tokens_ops.c \
		src/env/env_list.c src/env/env_str.c src/env/env_global.c src/env/env_init.c \

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