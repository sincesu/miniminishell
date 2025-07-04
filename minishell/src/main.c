#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/minishell.h"
#include "../Libft/libft.h"

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

int	quote_error(char *input, t_shell *shell)
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
				shell->exit_code = 2;
				return (1);
			}
		}
		if (input[i]) //check
			i++;
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
    if (parsed->flags) {
        for (i = 0; parsed->flags[i]; i++)
            printf("[%s] ", parsed->flags[i] ? parsed->flags[i] : "(null)");
        if (i == 0)
            printf("(none)");
    } else {
        printf("(none)");
    }
    printf("\n");

    // Args
    printf("Args    : ");
    if (parsed->args) {
        for (i = 0; parsed->args[i]; i++)
            printf("[%s] ", parsed->args[i] ? parsed->args[i] : "(null)");
        if (i == 0)
            printf("(none)");
    } else {
        printf("(none)");
    }
    printf("\n");

    printf("Input   : %s\n", parsed->input ? parsed->input : "(none)");
	printf("Output  : %s\n", parsed->output ? parsed->output : "(none)");


    printf("----------------------------\n");
}

int	syntax_error(t_shell *shell, t_parser *parsed)
{
	t_token *a;

	a = shell->args;
	while (a && a->content)
	{
		if(is_operator(a->content[0]))
		{
			if (a->type == R_APPEND)
			{
				if (!a->next)
				{
					printf("minishell: syntax error near unexpected token 'newline'\n");
					shell->exit_code = 2;
					return (1);
				}
				if (!is_operator(a->next->content[0]))
					parsed->output = a->next->content; //must be checked
				else
				{
					printf("minishell: syntax error near unexpected token `>>'\n");
					shell->exit_code = 2;
					return (1);
				}
			}
			else if (a->type == R_HERE)
			{
				if (!a->next)
				{
					printf("minishell: syntax error near unexpected token 'newline'\n");
					shell->exit_code = 2;
					return (1);
				}
				if (!is_operator(a->next->content[0]))
					parsed->input = a->next->content; //must be checked
				else
				{
					printf("minishell: syntax error near unexpected token `<<'\n");
					shell->exit_code = 2;
					return (1);
				}
			}
			else if (a->type == R_OUT)
			{
				if (!a->next)
				{
					printf("minishell: syntax error near unexpected token 'newline'\n");
					shell->exit_code = 2;
					return (1);
				}
				else if (!is_operator(a->next->content[0]))
					parsed->output = a->next->content;
			}
			else if (a->content[0] == '<')
			{
				if (!a->next)
				{
					printf("minishell: syntax error near unexpected token 'newline'\n");
					shell->exit_code = 2;
					return (1);
				}
				else if (!is_operator(a->next->content[0]))
					parsed->input = a->next->content;
			}
			else if (a->content[0] == '|')
			{
				if (!a->next)
				{
					printf("minishell: syntax error: unexpected end of file\n");
					shell->exit_code = 2;
					return (1);
				}
				else if (!is_operator(a->next->content[0]))
					; //must be checked
				else
				{
					printf("syntax error3\n");
					return (1);
				}
			}
		}
		a = a->next;
	}
	return (0);
}

int	operator_error(int c, t_shell *shell)
{
	if (c == '|')
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		shell->exit_code = 2;
		return (1);
	}
	return (0);
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
			if(quote_error(shell.input, &shell) || operator_error(shell.input[0], &shell))
				continue;
			shell.args = lexer(shell.input);
			if (!shell.args)
				continue;
			if(syntax_error(&shell, &parsed))
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
			else if (shell.args && ft_strncmp(shell.args->content, "env", 4) == 0)
				ft_env(shell.env);
			else if (shell.args && ft_strncmp(shell.args->content, "cd", 3) == 0)
				ft_cd(token_list_to_argv(shell.args)[1]);
			else if (shell.args && ft_strncmp(shell.args->content, "pwd", 4) == 0)
				ft_pwd();
			else if (shell.args && ft_strncmp(shell.args->content, "echo", 5) == 0)
				ft_echo(token_list_to_argv(shell.args)); //buraya tekrar bak
			else if (shell.args && ft_strncmp(shell.args->content, "exit", 5) == 0)
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
