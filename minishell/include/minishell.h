/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:58:24 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/29 17:27:40 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

enum
{
	R_OUT = 1,	// > redirection out
	R_APPEND,	// >>
	PIPE,		// |
	R_IN,		// redirection in
	R_HERE,		// << heredoc
	S_WORD,		// tek tırnak
	D_WORD,		// çift tırnak
	U_WORD,		// tırnaksız
};

typedef struct s_mem_list
{
	void				*block;
	struct s_mem_list	*next;
} 	t_mem_list;

typedef struct s_token
{
	char			*content;
	int				type;
	int				last;
	struct s_token	*next;
}	t_token;

typedef struct s_parser
{
	char	*command;
	char	**flags;
	char	**args;
	char	*input;
	char	*output;
}	t_parser;

/*
1-) 0. argüman kesinlikle komut
2-) 1. argüman ve sonrasında gelenlerden başında - olanlar komut
3-) 1. argümandan sonra gelen ve başında - olmayanlar input (| > >> < <<) olmadığı sürece
4-) 2. argümandan sonra gelen ve | olan bir token görürse önceki argümanı input olarak alıcak 
eğer sağında argüman yoksa outputu stdout'a verecek, argüman varsa argümana input olarak verecek,
*/

typedef struct s_shell
{
	//t_list	*collector; //burasına ihtiyaç duymayacağım.
	char	*input;
	t_token	*args;
	char	**env;
	int		exit_code;
}	t_shell;


char		**lexer_split(const	char *s);
t_token		*lexer(char *input);
void		expander(t_shell *shell);
t_mem_list	**get_head_mem();
int			is_whitespace(char c);
int			skip_whitespace(char *str);
int			is_operator(char c);
int			is_quote(char c);
int			create_operator(char *str, t_token **head_list);
int			get_word_type(char c);
int			create_word(char *str, t_token **head_list);
int			create_delimn(char *str, t_token **head_list);
void		ft_free();
void		safe_abort(int exit_code);
void		register_alloc_mem(void *ptr);
void		*ft_alloc(unsigned long size);

void	ft_cd(const char *path);
int		ft_pwd(void);
int		ft_echo(char **args);
void	ft_exit(char *arg, t_shell *shell);
void	parser(t_shell *shell, t_parser *parsed);

int			env_len(char **env);
char		**copy_env(char **env);
void		print_env(char **env_copy);

t_token		*ft_lstnew_token(t_token token);
void		ft_lstadd_back_token(t_token **lst, t_token *new_node);
void		ft_lstclear_token(t_token **lst, void (*del)(void *));
void		ft_lstdelone_token(t_token *lst, void (*del)(void *));
int			ft_lstsize_token(t_token *lst);
t_token		*ft_lstlast_token(t_token *lst);

void		ft_handle_sigint(int signum);
void		ft_handle_sigquit(int signum);
void		ft_init_signals(void);


#endif
