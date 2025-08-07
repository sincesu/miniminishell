/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:58:24 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/07 22:12:06 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum e_token_type
{
	R_OUT = 1,
	R_APPEND,
	PIPE,
	R_IN,
	R_HERE,
	S_WORD,
	D_WORD,
	U_WORD
}	t_token_type;

typedef struct s_mem_list
{
	void				*block;
	struct s_mem_list	*next;
}	t_mem_list;

typedef struct s_token
{
	char			*content;
	int				type;
	int				flag;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_redirect
{
	char				*file_name;
	int					type;
	int					flags;
	char				*document;
}	t_redirect;

typedef struct s_parser
{
	char			**args;
	t_redirect		*redirect;
	int				redirect_count;
	int				fd_in;
	int				fd_out;
	struct s_parser	*prev;
	struct s_parser	*next;
}	t_parser;

typedef struct s_shell
{
	char	*input;
	char	*old_input;
	t_token	*args;
	char	**env;
	char	**export_only_list;
	int		exit_code;
}	t_shell;

extern int	g_signal_received;

typedef enum e_signal_type
{
	PROMPT,
	EXECUTION,
	HEREDOC,
	IGNORE
}	t_signal_type;

//expander ++OKEY
void		expander(t_shell *shell);
char		*find_dollar(char *input, char **env, int flag, int exit_code);
int			handle_dollar_sequence(char *input, char **expanded,
				char **env, int exit_code);
int			handle_normal_char(char *input, char **expanded);

//builtins
int			ft_cd(t_shell *shell, t_parser *parser);
int			ft_pwd(t_shell *shell);
int			ft_echo(char **args);
void		ft_exit(t_shell *shell, t_parser *parsed);
int			ft_unset(t_shell *shell, t_parser *parsed);

//env
int			ft_env(t_shell *shell, t_parser *parsed);
char		**copy_env(char **env);
void		set_underscore_env(t_token *args, t_shell *shell);
char		*find_in_env(char **env, char *name);
int			find_in_env_index(char **env, char *name);

//export
int			ft_export(t_shell *shell, t_parser *parsed);
int			is_valid_identifier(t_shell *shell, char *arg, int str_len);
void		bubble_sort(char **arr);
void		update_env_value(char **env, int idx, char *name, char *eq);
void		append_env_variable(t_shell *shell, char *content);
void		handle_export_arg(t_shell *shell, char *arg);

//pattern.c
int			is_whitespace(char c);
int			skip_whitespace(char *str);
int			is_operator(char c);
int			is_quote(char c);
int			syntax_error(t_shell *shell);
int			operator_error(int c, t_shell *shell);
int			quote_error(char *input, t_shell *shell);
int			is_redirection_type(int type);
int			is_operator_token(const char *s);

//lexer
t_token		*lexer(char *input);
int			count_tokens(const char *s);
void		fill_tokens_and_flags(const char *s, char **res, int *flags);

t_mem_list	**get_head_mem(void);
void		ft_free(void);
void		safe_abort(int exit_code);
void		register_alloc_mem(void *ptr);
void		*ft_alloc(unsigned long size);

//merger
void		merger(t_token *args);

//parser
t_parser	*parser(t_token	*token);
t_parser	*new_node(t_parser current);
int			arg_len_counter(t_token *token);
int			red_len_counter(t_token *token);

//listeler
t_token		*ft_lstnew_token(t_token token);
void		ft_lstadd_back_token(t_token **lst, t_token *new_node);
void		ft_lstclear_token(t_token **lst, void (*del)(void *));
void		ft_lstdelone_token(t_token *lst, void (*del)(void *));
int			ft_lstsize_token(t_token *lst);
t_token		*ft_lstlast_token(t_token *lst);

//signal kısmı
void		ft_init_signals(t_signal_type signum);
void		ft_prompt_handler(int signum);
void		ft_sigquit_handler(int signum);
void		ft_execute_handler(int signum);
void		ft_heredoc_handler(int signum);

//executer kısmı
void		ft_execute_commands(t_shell *shell, t_parser *parsed);
int			ft_shell_command(t_shell *shell, t_parser *parsed);
int			ft_one_command(t_shell *shell, t_parser *parsed);
int			ft_multi_command(t_shell *shell, t_parser *parsed);
int			handle_heredoc(t_shell *shell, t_parser *parsed);
void		ft_execute_external_command(char *path, t_parser *parsed,
				char **env);
void		check_command_errors(char *path, t_parser *parsed);
void		init_command_redirections(t_parser *parsed, int **pipes,
				int cmd_count);

int			ft_apply_redirections(t_redirect *redir, int redirect_count, int i);
int			ft_is_builtin(char *cmd);
int			ft_execute_builtin(t_shell *shell, t_parser *parsed);
char		*ft_search_command_path(char *command);
char		*ft_get_heredoc_input(const char *delimiter, t_shell *shell,
				int flag);

int			ft_count_commands(t_parser *parsed);
int			ft_create_pipes(int **pipes, int count);
void		ft_close_all_pipes(int **pipes, int count);
void		ft_perror(char *pname, char *target, char *err);

#endif
