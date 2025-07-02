#include <stdio.h>

void	ft_env(char **env_copy)
{
	int i;

	i = 0;
	while (env_copy[i])
		printf("%s\n", env_copy[i++]);
}