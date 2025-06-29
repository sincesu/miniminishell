#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/minishell.h"
#include "../Libft/libft.h"

void	ft_cd(const char *path);
int		ft_pwd(void);
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

int	syntax_error(char *input, t_shell *shell)
{
	int i;
	char quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] != quote)
			{
				printf("minishell: syntax error: unmatched quote\n");
				shell->exit_code = 1;
				return (1);
			}
		}
		if (input[i])
			i++;
	}
	if (input[0] && input[0] == '|')
	{
		printf("minishell: syntax error: near unexpected token '|'\n");
		shell->exit_code = 1;
		return (1);
	}
	return (0);
}

void mini_parser_debugger(t_parser *parsed)
{
    int i;

    printf("----- MINI PARSER DEBUG -----\n");

    // Komut
    printf("Command : %s\n", parsed->command ? parsed->command : "(none)");

    // Flags
    printf("Flags   : ");
    if (parsed->flags)
    {
        for (i = 0; parsed->flags[i]; i++)
            printf("[%s] ", parsed->flags[i]);
        if (i == 0)
            printf("(none)");
    }
    else
        printf("(none)");
    printf("\n");

    // Args
    printf("Args    : ");
    if (parsed->args)
    {
        for (i = 0; parsed->args[i]; i++)
            printf("[%s] ", parsed->args[i]);
        if (i == 0)
            printf("(none)");
    }
    else
        printf("(none)");
    printf("\n");

    printf("----------------------------\n");
}




int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_shell shell;
	t_parser parsed;
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
        	ft_exit(NULL, &shell);
        	break ;
    	}
		if (*shell.input)
		{
			add_history(shell.input);
			if(syntax_error(shell.input, &shell))
				continue;
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
			
			parser(&shell, &parsed);
			mini_parser_debugger(&parsed);

			
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
				ft_exit(shell.args->content, &shell);
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
