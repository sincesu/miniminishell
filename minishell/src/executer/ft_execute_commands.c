#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stddef.h>

char	**token_list_to_argv(t_token *tokens)
{
	int	size;
	char **av;
	int i;

	size = ft_lstsize_token(tokens);
	av = ft_alloc(sizeof(char *) * (size + 1));
	i = 0;
	while (tokens)
	{
		av[i++] = tokens->content;
		tokens = tokens->next;
	}
	av[i] = NULL;
	return (av);
}

void	ft_one_command(t_shell shell)
{
	if (shell.args && ft_strncmp(shell.args->content, "env", 4) == 0)
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
#include <stdio.h>

void	ft_multi_command(t_shell shell)
{
	printf("multi command\n");
	(void)shell;
}

int	ft_is_multi_command(t_shell shell)
{
	t_token	*token;

	token = shell.args;
	while (token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

void    ft_execute_commands(t_shell shell)
{
	if (ft_is_multi_command(shell))
		ft_multi_command(shell);
	else
		ft_one_command(shell);
}