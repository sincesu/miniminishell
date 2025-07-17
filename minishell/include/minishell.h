/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:58:24 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/17 18:56:35 by saincesu         ###   ########.fr       */
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
	U_WORD,
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
	struct s_redirect	*next;
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

char		**lexer_split(const char *s, int **flag_array);
t_token		*lexer(char *input);
void		expander(t_shell *shell);
t_mem_list	**get_head_mem(void);
int			is_whitespace(char c);
int			skip_whitespace(char *str);
int			is_operator(char c);
int			is_quote(char c);
int			create_operator(char *str, t_token **head_list);
int			get_word_type(char c);
int			create_word(char *str, t_token **head_list);
int			create_delimn(char *str, t_token **head_list);
void		ft_free(void);
void		safe_abort(int exit_code);
void		register_alloc_mem(void *ptr);
void		*ft_alloc(unsigned long size);
int			is_operator_type(int type);
int			tokenize(char *str);
char		*ft_handle_oldpwd(void);
void		remove_empty_tokens(t_token **head);
void		merger(t_token	*a);
char		*find_dollar(char *input, char **env, int flag);
char		**update_shell_lvl(char **env);

int			r_append_error(t_token *a, t_shell *shell);
int			r_here_error(t_token *a, t_shell *shell);
int			r_in_and_r_out_error(t_token *a, t_shell *shell);
int			pipe_error(char *str, t_token *a, t_shell *shell);
int			syntax_error(t_shell *shell);
int			operator_error(int c, t_shell *shell);
int			quote_error(char *input, t_shell *shell);

int			ft_cd(t_shell *shell, t_parser *parser);
int			ft_pwd(void);
int			ft_echo(char **args);
void		ft_exit(t_shell *shell);
int			ft_env(char **env_copy);
int			ft_unset(t_shell *shell);
int			ft_export(t_shell *shell);

int			is_remove_env(char *env_var, t_token *head);
char		**copy_env_without_unset(char **env, t_token *head);
int			index_searcher(char *s, int c);
int			export_count(char **str);
int			arg_counter(t_token *token);
char		*find_in_env(char **env, char *name);
int			find_in_env_index(char **env, char *name);
void		export_list_printer(t_shell *shell);
void		update_env_value(char **env, int idx, char *name, char *eq);
void		append_env_variable(t_shell *shell, char *content);
int			handle_var_expand(char *s, char **env, char **expanded);
int			handle_normal_char(char *input, char **expanded);
int			handle_dollar(char *input, char **env, char **expanded);
t_parser	*parser(t_token	*token);
int			env_len(char **env);
char		**copy_env(char **env);
int			arg_len_counter(t_token *token);
int			red_len_counter(t_token *token);
t_parser	*new_node(t_parser current);
char		*fill_dolar(char *input, char **env, int var_len);
int			is_operator_token(const char *s);

t_token		*ft_lstnew_token(t_token token);
void		ft_lstadd_back_token(t_token **lst, t_token *new_node);
void		ft_lstclear_token(t_token **lst, void (*del)(void *));
void		ft_lstdelone_token(t_token *lst, void (*del)(void *));
int			ft_lstsize_token(t_token *lst);
t_token		*ft_lstlast_token(t_token *lst);

//signal kısmı
void		ft_handle_sigint(int signum);
void		ft_handle_sigquit(int signum);
void		ft_init_signals(void);

//executer kısmı
void		ft_execute_commands(t_shell *shell, t_parser *parsed);
int			ft_shell_command(t_shell *shell, t_parser *parsed);
int			ft_one_command(t_shell *shell, t_parser *parsed);
int			ft_multi_command(t_shell *shell, t_parser *parsed);

int			ft_apply_redirections(t_redirect *redir);
int			ft_is_builtin(char *cmd);
int			ft_execute_builtin(t_shell *shell, t_parser *parsed);
char		*ft_search_command_path(char *command);
char		*ft_get_heredoc_input(const char *delimiter, t_shell *shell, t_parser parsed);

// parser
t_parser	ft_parse_command(t_shell *shell, t_parser parsed);
t_redirect	*ft_process_redirects(t_shell *shell, t_parser parser);
void	ft_initialize_parser(t_parser *parser, t_parser parsed);
void	ft_count_args_redirects(t_token *tokens, int *arg_count, 
		int *redirect_count);
void	ft_process_args(t_shell *shell, t_parser *parser);

#endif
