#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <readline/readline.h>
#include <stdlib.h>

char *ft_get_heredoc_input(const char *delimiter, t_shell *shell, t_parser parsed)
{
    char *line;
    char *result = ft_strdup("");
    char *temp;

    if (!delimiter || !shell)
        return (NULL);
    while (1)
    {
        line = readline("> ");
        if (!line)
			safe_abort(0);
        if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
        {
            free(line);
            break;
        }
        if (parsed.redirect && parsed.redirect->flags == U_WORD)
            temp = ft_strjoin(result, find_dollar(line, shell->env, 0));
        else
            temp = ft_strjoin(result, line);
        free(line);
        result = ft_strjoin(temp, "\n");
    }
    return (result);
}