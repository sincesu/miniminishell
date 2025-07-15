/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:58:24 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/15 12:06:28 by saincesu         ###   ########.fr       */
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
	//int				last;
	int				flag;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_redirect
{
	char	*file_name;
	int		type;
	int		flags;
	char	*document;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_exec_unit
{
    char        **args;
    t_redirect  *redirect;
}   t_exec_unit;

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

char 		**lexer_split(const char *s, int **flag_array);
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
void		remove_empty_tokens(t_token **head);
void		merger(t_token	*a);
char		*find_dollar(char *input, char **env, int flag);

int			r_append_error(t_token *a, t_shell *shell);
int			r_here_error(t_token *a, t_shell *shell);
int			r_in_and_r_out_error(t_token *a, t_shell *shell);
int			pipe_error(char *str, t_token *a, t_shell *shell);
int			syntax_error(t_shell *shell);
int			operator_error(int c, t_shell *shell);
int			quote_error(char *input, t_shell *shell);

void		ft_cd(const char *path);
int			ft_pwd(void);
int			ft_echo(char **args);
void		ft_exit(t_shell *shell);
void		ft_env(char **env_copy);

int		is_remove_env(char *env_var, t_token *head);
char	**copy_env_without_unset(char **env, t_token *head);
void	ft_unset(t_shell *shell);
int		index_searcher(char *s, int c);
int		export_count(char **str);
int		arg_counter(t_token *token);
char	*find_in_env(char **env, char *name);
int		find_in_env_index(char **env, char *name);
void	ft_export(t_shell *shell);
void	export_list_printer(t_shell *shell);
void	update_env_value(char **env, int idx, char *name, char *eq);
void	append_env_variable(t_shell *shell, char *content);


t_parser	*parser(t_token	*token);
int			env_len(char **env);
char		**copy_env(char **env);
int			arg_len_counter(t_token *token);
int			red_len_counter(t_token *token);
t_parser	*new_node(t_parser current);
char		*fill_dolar(char *input, char **env ,int var_len);
int			is_operator_token(const char *s);

t_token		*ft_lstnew_token(t_token token);
void		ft_lstadd_back_token(t_token **lst, t_token *new_node);
void		ft_lstclear_token(t_token **lst, void (*del)(void *));
void		ft_lstdelone_token(t_token *lst, void (*del)(void *));
int			ft_lstsize_token(t_token *lst);
t_token		*ft_lstlast_token(t_token *lst);

void		ft_handle_sigint(int signum);
void		ft_handle_sigquit(int signum);
void		ft_init_signals(void);

void		ft_execute_commands(t_shell *shell, t_parser parsed);
int			ft_shell_command(t_shell *shell, t_exec_unit *parsed);
void		ft_one_command(t_shell *shell, t_parser parsed);
void		ft_multi_command(t_shell *shell, t_parser parsed);

int			ft_apply_redirections(t_redirect *redir);
int			ft_is_builtin(char *cmd);
void		ft_execute_builtin(t_shell *shell, t_exec_unit *unit);

#endif
