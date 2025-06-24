#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void ft_cd(const char *path)
{
    char    *cwd;
	
	if (path == NULL)
		getcwd("~", 1);
    if (chdir(path) == -1)
    {
        perror("cd");
        return;
    }
    cwd = (char *)malloc(PATH_MAX);
    if (!cwd)
    {
        perror("malloc");
        return;
    }
    if (getcwd(cwd, PATH_MAX))
    {}
    else
        perror("getcwd");
    free(cwd);
}
