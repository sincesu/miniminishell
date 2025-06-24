#include <unistd.h>
#include <stdlib.h>
#include "../../Libft/libft.h"

void	ft_exit(char *arg)
{
	int	exit_code;

	if (arg == NULL)
		exit(0);
	exit_code = ft_atoi(arg);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(exit_code);
}
