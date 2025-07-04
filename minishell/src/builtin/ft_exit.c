/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:53:24 by saincesu          #+#    #+#             */
/*   Updated: 2025/06/29 14:07:30 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../../Libft/libft.h"
#include "../../include/minishell.h"
#include <stdio.h>

static int ft_check_param(char *str)
{
    int i = 0;
    
    if (!str)
        return (1);
    if (str[0] == '-' || str[0] == '+')
        i = 1;
    if (str[i] == '\0')
        return (1);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (1);
        i++;
    }
    return (0);
}

void ft_exit(t_shell *shell)
{
    int exit_code;
    
    if (shell->args->next == NULL)
    {
        printf("exit\n");
        safe_abort(shell->exit_code);
        return;
    }
    if (ft_check_param(shell->args->next->content))
    {
        printf("exit\n");
        printf("minishell: exit: %s: numeric argument required\n",
               shell->args->next->content);
        safe_abort(shell->exit_code);
        return;
    }
    if (shell->args->next->next)
    {
        printf("exit\n");
        printf("minishell: exit: too many arguments\n");
        return ;
    }
    exit_code = ft_atoi(shell->args->next->content);
    printf("exit\n");
    safe_abort(exit_code);
}