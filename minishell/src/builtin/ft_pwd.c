#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../Libft/libft.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("PWD: ERROR");
		return (0);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (1);
}
