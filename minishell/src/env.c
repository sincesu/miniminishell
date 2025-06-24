#include "../include/minishell.h"
#include "../Libft/libft.h"
#include <stdio.h>

int	env_len(char **env)
{
	int i;

	i = 0;
	while(env[i])
		i++;
	return (i);
}

char	**copy_env(char **env)
{
	int i;
	int env_line;
	char **copy_env;

	i = 0;
	copy_env = NULL;

	env_line = env_len(env);
	copy_env = ft_alloc(sizeof(char *) * (env_line + 1));
	while(i < env_line)
	{
		copy_env[i] = ft_alloc(ft_strlen(env[i]) + 1);
		ft_strlcpy(copy_env[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	copy_env[env_line] = NULL;
	return (copy_env);
}

void	print_env(char **env_copy)
{
	int i;

	i = 0;
	while (env_copy[i])
		printf("%s\n", env_copy[i++]);
}
