NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
LIBFT_DIR	= Libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

SRCS	= 	src/main.c src/allocator/allocator.c src/builtin/ft_cd.c \
			src/builtin/ft_echo.c src/builtin/ft_env.c src/builtin/ft_exit.c src/builtin/ft_pwd.c \
			src/lexer/lexer.c src/lexer/pattern.c src/list/ft_lstadd_back_token.c src/executer/ft_execute_commands.c \
			src/executer/ft_multi_command.c src/executer/ft_one_command.c src/executer/ft_shell_commands.c src/executer/token_list_to_argv.c \
			src/list/ft_lstclear_token.c src/list/ft_lstdelone_token.c src/list/ft_lstlast_token.c \
			src/list/ft_lstnew_token.c src/list/ft_lstsize_token.c src/env.c src/signal.c src/lexer/lexer_split.c \
			src/expander/expander.c src/parser/parser.c src/syntax_error/quote_error.c src/syntax_error/syntax_error.c \
			src/merger/merger.c 

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -lreadline -o $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

#makefile düzenle
