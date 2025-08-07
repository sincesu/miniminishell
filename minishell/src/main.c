/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:35:09 by saincesu          #+#    #+#             */
/*   Updated: 2025/08/07 18:52:50 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../Libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

static void	ft_get_shell_input(t_shell *shell)
{
	ft_init_signals(PROMPT);
	shell->old_input = readline("minishell> ");
	if (!shell->old_input)
	{
		ft_putendl_fd("exit", 1);
		safe_abort(0);
	}
	shell->input = ft_strdup(shell->old_input);
	free(shell->old_input);
}

void	ft_process_shell_input(t_shell *shell)
{
	t_parser	*parsed;

	add_history(shell->input);
	if (quote_error(shell->input, shell)
		|| operator_error(shell->input[0], shell))
		return ;
	shell->args = lexer(shell->input);
	if (!shell->args)
		return ;
	if (syntax_error(shell))
		return ;
	expander(shell);
	merger(shell->args);
	set_underscore_env(shell->args, shell);
	parsed = parser(shell->args);
	if (!shell->args)
		return ;
	if (ft_handle_heredoc(shell, parsed))
		return ;
	ft_execute_commands(shell, parsed);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)av;
	if (ac != 1)
		return (1);
	ft_bzero(&shell, sizeof(t_shell));
	shell.env = copy_env(env);
	shell.exit_code = 0;
	while (1)
	{
		ft_get_shell_input(&shell);
		ft_process_shell_input(&shell);
	}
	safe_abort(0);
}
