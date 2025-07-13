#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/minishell.h"
#include "../Libft/libft.h"

void mini_parser_debugger(t_parser *parsed)
{
	int i = 0;

	printf("----- MINI PARSER DEBUG -----\n");

	// Args
	printf("Args    : ");
	if (parsed->args)
	{
		while (parsed->args[i])
			printf("[%s] ", parsed->args[i++]);
		if (i == 0)
			printf("(none)");
	}
	else
		printf("(none)");
	printf("\n");

	// Redirects
	printf("Redirects (%d):\n", parsed->redirect_count);
	if (parsed->redirect && parsed->redirect_count > 0)
	{
		for (i = 0; i < parsed->redirect_count; i++)
		{
			printf("  - type: %d | file: %s", parsed->redirect[i].type,
				parsed->redirect[i].file_name ? parsed->redirect[i].file_name : "(none)");
			printf(" | flags: %d", parsed->redirect[i].flags);
			if (parsed->redirect[i].document)
				printf(" | document: %s", parsed->redirect[i].document);
			printf("\n");
		}
	}
	else
		printf("  (none)\n");

	// fd_in / fd_out
	printf("fd_in   : %d\n", parsed->fd_in);
	printf("fd_out  : %d\n", parsed->fd_out);

	printf("----------------------------\n");
}


int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_shell shell;
	t_parser *parsed;
	ft_bzero(&shell, sizeof(t_shell));
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
			safe_abort(0);
    		//ft_exit(&shell);
    		break;
		}
		shell.input = ft_strdup(shell.old_input);
		free(shell.old_input);
		if (!shell.input)
		{
	    	safe_abort(0);
    		//ft_exit(&shell);
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
			merger(shell.args);

			//TOKEN YAZDIRMA KISMI
			// t_token *tmp = shell.args;
			// while (tmp)
			// {
			// 	printf("TOKEN: [%s] (type: %d) (flag: %d)\n", tmp->content, tmp->type, tmp->flag);
			// 	tmp = tmp->next;
			// }

			parsed = parser(shell.args);
			//mini_parser_debugger(parsed);

			if (!shell.args)
				return 1;
			else
				ft_execute_commands(&shell, *parsed);
		}
	}
	safe_abort(0);
	return 0;
}
