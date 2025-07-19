#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <readline/readline.h>

int	*ft_exit_status(void)
{
	static int	status = 0;

	return (&status);
}

void	ft_prompt_handler(int signum)
{
	g_signal_received = signum;
	ft_putendl_fd("", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	*ft_exit_status() = 1;
}

void	ft_sigquit_handler(int signum)
{
	g_signal_received = signum;
	ft_putendl_fd("Quit (core dumped)", 2);
	*ft_exit_status() = 131;
}

void	ft_execute_handler(int signum)
{
	g_signal_received = signum;
	ft_putendl_fd("", 1);
	*ft_exit_status() = 130;
}

void	ft_heredoc_handler(int signum)
{
	g_signal_received = signum;
	rl_done = 1;
	ft_putendl_fd("", 1);
	*ft_exit_status() = 130;
}
