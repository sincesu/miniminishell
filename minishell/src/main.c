/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:35:09 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/23 19:22:41 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../Libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_get_shell_input(t_shell *shell)
{
	ft_init_signals(PROMPT);
	shell->old_input = readline("minishell> ");
	if (!shell->old_input)
	{
		safe_abort(0);
		return (0);
	}
	shell->input = ft_strdup(shell->old_input);
	free(shell->old_input);
	if (!shell->input)
	{
		safe_abort(0);
		return (0);
	}
	return (1);
}

void	ft_process_shell_input(t_shell *shell)
{
	t_parser	*parsed;

	if (*shell->input)
	{
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
		ft_execute_commands(shell, parsed);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	ft_bzero(&shell, sizeof(t_shell));
	shell.env = copy_env(env);
	shell.env = update_shell_lvl(shell.env);
	shell.exit_code = 0;
	if (!shell.env)
		return (1);
	while (1)
	{
		if (!ft_get_shell_input(&shell))
			break ;
		ft_process_shell_input(&shell);
	}
	safe_abort(0);
	return (0);
}
