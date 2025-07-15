#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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

void    ft_execute_commands(t_shell *shell, t_parser parsed)
{
	if (ft_is_multi_command(*shell))
		shell->exit_code = ft_multi_command(shell, parsed);
	else
		shell->exit_code = ft_one_command(shell, parsed);
}