/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:52:05 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/23 16:00:52 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

void	ft_lstdelone_token(t_token *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst); // bu satırı garbage collector'da double free yememek için silinebilir.
	}
}

//bunun yerine free_ptr yaz. allocator için

//yapılacaklr listesi
//t_list yapısından kurtulup onun yerine tokenize yapısı yapılacak.
//boktan minishell.h yerleri düzenlenecek.
//main.c'deki garbage_collector yazan satırı düzenle.
//main.c deki 39.satırdaki lexer'ın dönüş değerine bak