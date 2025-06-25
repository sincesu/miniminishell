#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/minishell.h"
#include "../Libft/libft.h"

void	ft_cd(const char *path);
int		ft_pwd(void);
void	ft_exit(char *arg);
int		ft_echo(char **args);


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	**token_list_to_argv(t_token *tokens)
{
	int	size;
	char **av;
	int i;

	size = ft_lstsize_token(tokens);
	av = ft_alloc(sizeof(char *) * size + 1); //garbage collector'a eklenmesi gerekiyor.
	i = 0;
	while (tokens)
	{
		av[i++] = tokens->content;
		tokens = tokens->next;
	}
	av[i] = NULL;
	return (av);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_shell shell;
	shell.env = copy_env(env);
	shell.exit_code = 0;
	if (!shell.env)
		return (1);
	ft_init_signals();
	while (1)
	{
		shell.input = readline("minishell> ");
		if (!shell.input)
  		{
        	printf("exit\n");
        	ft_exit(0);
        	break ;
    	}
		if (*shell.input)
		{
			add_history(shell.input);
			shell.args = lexer(shell.input); //bu satıra bak bugün
			if (!shell.args)
				continue;
			expander(&shell);
			
			//TOKEN YAZDIRMA KISMI
			t_token *tmp = shell.args;
			while (tmp)
			{
				printf("TOKEN: [%s] (type: %d)\n", tmp->content, tmp->type);
				tmp = tmp->next;
			}
			
			if (!shell.args)
				return 1;
			if (shell.args && strcmp(shell.args->content, "env") == 0)
				print_env(shell.env);
			if (shell.args && ft_strncmp(shell.args->content, "cd", 2) == 0)
				ft_cd(token_list_to_argv(shell.args)[1]);
			else if (shell.args && strcmp(shell.args->content, "pwd") == 0)
				ft_pwd();

			else if (shell.args && strcmp(shell.args->content, "echo") == 0)
				ft_echo(token_list_to_argv(shell.args)); //buraya tekrar bak

			else if (shell.args && strcmp(shell.args->content, "exit") == 0)
				ft_exit(shell.args->content);
			// else
			// {
			// 	t_token *tmp = shell.args;
			// 	while(tmp)
			// 	{
			// 		printf("%s\n", tmp->content);
			// 		tmp = tmp->next;
			// 	}
			// }
		}
		
		free(shell.input);
	}
	safe_abort(0);
	return 0;
}
