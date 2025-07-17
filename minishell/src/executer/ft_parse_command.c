#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

t_parser	ft_parse_command(t_shell *shell, t_parser parsed)
{
	t_parser	parser;
	int			arg_count;
	int			redirect_count;

	ft_initialize_parser(&parser, parsed);
	ft_count_args_redirects(shell->args, &arg_count, &redirect_count);
	parser.args = ft_alloc(sizeof(char *) * (arg_count + 1));
	parser.redirect_count = redirect_count;
	parser.redirect = ft_process_redirects(shell, parser);
	ft_process_args(shell, &parser);
	return (parser);
}
