#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	tokenize(char *str)
{
	if (strcmp(str, ">") == 0)
		return (R_OUT);
	if (strcmp(str, ">>") == 0)
		return (R_APPEND);
	if (strcmp(str, "|") == 0)
		return (PIPE);
	if (strcmp(str, "<") == 0)
		return (R_IN);
	if (strcmp(str, "<<") == 0)
		return (R_HERE);

	int len = ft_strlen(str);
	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		return (S_WORD);
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (D_WORD);

	return (U_WORD);
}


t_token	*lexer(char *input)
{
	char **str;
	int tmp_token;
	t_token *head_list;
	int i;

	i = 0;
	head_list = NULL;
	str = lexer_split(input);
	if (!str)
		return NULL;
	while (str[i])
	{
		tmp_token = tokenize(str[i]);
		ft_lstadd_back_token(&head_list, ft_lstnew_token((t_token){
			.content = ft_strdup(str[i]), .type = tmp_token , .last = 0, .next = NULL}));
		i++;
	}
	return (head_list);
}
