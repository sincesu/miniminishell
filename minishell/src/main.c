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
	av = ft_alloc(sizeof(char *) * size + 1);
	i = 0;
	while (tokens)
	{
		av[i++] = tokens->content;
		tokens = tokens->next;
	}
	av[i] = NULL;
	return (av);
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


int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_shell shell;
	t_parser parsed;
	ft_bzero(&shell, sizeof(t_shell));
	ft_bzero(&parsed, sizeof(t_parser));
	shell.env = copy_env(env);
	shell.exit_code = 0;
	if (!shell.env)
		return (1);
	ft_init_signals();
	while (1)
	{
		shell.old_input = readline("minishell> ");
		if (!shell.old_input)
		{
    		ft_exit(&shell);
    		break;
		}
		shell.input = ft_strdup(shell.old_input);
		free(shell.old_input);
		if (!shell.input)
		{
	    	ft_exit(&shell);
    		break;
		}
		if (*shell.input)
		{
			add_history(shell.input);
			if(quote_error(shell.input, &shell) || operator_error(shell.input[0], &shell))
				continue;
			shell.args = lexer(shell.input);
			if (!shell.args)
				continue;
			if(syntax_error(&shell))
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
				ft_exit(&shell);
		}
	}
	safe_abort(0);
	return 0;
}
