#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdio.h>

void	ft_one_command(t_shell shell)
{
	if (shell.args && ft_strncmp(shell.args->content, "echo", 5) == 0)
		ft_echo(token_list_to_argv(shell.args)); //buraya tekrar bak
	else if (shell.args && ft_strncmp(shell.args->content, "cd", 3) == 0)
    	ft_cd(token_list_to_argv(shell.args)[1]);
	else if (shell.args && ft_strncmp(shell.args->content, "pwd", 4) == 0)
		ft_pwd();
	else if (shell.args && ft_strncmp(shell.args->content, "export", 7) == 0)
		printf("export\n");
	else if (shell.args && ft_strncmp(shell.args->content, "unset", 6) == 0)
		printf("unset\n");
	else if (shell.args && ft_strncmp(shell.args->content, "env", 4) == 0)
		ft_env(shell.env);
	else if (shell.args && ft_strncmp(shell.args->content, "exit", 5) == 0)
		ft_exit(&shell);
	else
		ft_shell_commands(&shell);
}