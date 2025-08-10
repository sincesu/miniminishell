NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT_DIR   = Libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

SRCS		= src/allocator/allocator.c src/builtin/ft_cd.c src/builtin/ft_echo.c src/builtin/ft_env.c src/builtin/ft_exit.c src/builtin/ft_export_utils.c \
				src/builtin/ft_export.c src/builtin/ft_pwd.c src/builtin/ft_unset.c src/executer/ft_builtin_utils.c src/executer/ft_execute_commands.c \
				src/executer/ft_get_heredoc_input.c src/executer/ft_multi_command_utils.c src/executer/ft_multi_command.c src/executer/ft_one_command.c \
				src/executer/ft_search_command_path.c src/executer/ft_shell_command.c src/expander/expander.c src/expander/expander_utils.c src/lexer/lexer.c \
				src/lexer/lexer_utils.c src/lexer/pattern.c src/list/ft_lstadd_back_token.c \
				src/list/ft_lstlast_token.c src/list/ft_lstnew_token.c src/main.c src/merger/merger.c src/parser/parser.c \
				src/parser/parser_utils.c src/redirection/ft_apply_redirection.c src/signal/ft_init_signals.c src/signal/signal_handlers.c src/syntax_error/quote_error.c \
				src/syntax_error/syntax_error.c src/ft_perror.c src/builtin/ft_env_utils.c src/executer/ft_handle_heredoc.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -lreadline -o $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
