#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <fcntl.h>
#include <unistd.h>

char *get_heredoc_input(const char *delimiter, t_shell *shell, t_parser parsed)
{
    char *line;
    char *result = ft_strdup("");
    char *temp;

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
        if (parsed.redirect->flags == U_WORD)
            temp = ft_strjoin(result, find_dollar(line, shell->env, 0));
        else
            temp = ft_strjoin(result, line);
        free(line);
        result = ft_strjoin(temp, "\n");
    }
    return (result);
}

int ft_apply_redirections(t_redirect *redir)
{
    while (redir)
    {
        int fd;

        if (redir->type == R_IN)
        {
            fd = open(redir->file_name, O_RDONLY);
            if (fd == -1)
            {
                perror("infile");
                return (-1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (redir->type == R_OUT)
        {
            fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror("outfile");
                return (-1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redir->type == R_APPEND)
        {
            fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                perror("append");
                return (-1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redir->type == R_HERE)
        {
            int pipefd[2];
            if (pipe(pipefd) == -1)
            {
                perror("pipe");
                return (-1);
            }
            if (redir->document)
                write(pipefd[1], redir->document, ft_strlen(redir->document));
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
        }
        redir = redir->next;
    }
    return (0);
}

t_exec_unit parse_exec_unit(t_shell *shell, t_parser parsed)
{
    t_exec_unit unit;
    int arg_count;
    int i;
    int prev_type;
    
    // Args için yer sayısını hesapla
    t_token *temp = shell->args;
    arg_count = 0;
    i = 0;
    while (temp)
    {
        if (temp->type == S_WORD || temp->type == D_WORD || temp->type == U_WORD)
        {
            prev_type = 0;
            if (temp->prev)
                prev_type = temp->prev->type;
            // Eğer önceki token redirection operatörü değilse, bu bir argümandır
            if (temp == shell->args || !is_operator_type(prev_type))
                arg_count++;
        }
        temp = temp->next;
    }
    unit.args = ft_alloc(sizeof(char *) * (arg_count + 1));
    unit.redirect = NULL;
    t_redirect *head = NULL;
    t_redirect *tail = NULL;
    temp = shell->args;
    while (temp)
    {
        if (is_operator_type(temp->type))
        {
            t_redirect *redir = ft_alloc(sizeof(t_redirect));
            redir->type = temp->type;
            redir->flags = 0;
            redir->document = NULL;
            redir->next = NULL;
           if (temp->next && (temp->next->type == S_WORD ||
                   temp->next->type == D_WORD ||
                   temp->next->type == U_WORD))
            {
                redir->file_name = ft_strdup(temp->next->content);
                if (temp->type == R_HERE)
                    redir->document = get_heredoc_input(temp->next->content, shell, parsed);

                temp = temp->next; // Dosya adını atla
            }
            if (!head)
                head = redir;
            else
                tail->next = redir;
            tail = redir;
        }
        else if (temp->type == S_WORD || temp->type == D_WORD || temp->type == U_WORD)
        {
            // Eğer önceki token redirection operatörü değilse, bu bir argümandır
            if (temp == shell->args || !is_operator_type(temp->prev ? temp->prev->type : 0))
            {
                unit.args[i++] = temp->content;
            }
        }
        temp = temp->next;
    }
    
    unit.args[i] = NULL;
    unit.redirect = head;
    return unit;
}

int ft_one_command(t_shell *shell, t_parser parsed)
{
    (void)parsed;
    t_exec_unit unit = parse_exec_unit(shell, parsed);
    
    if (!unit.args || !unit.args[0])
        return (500);
    int saved_stdin = -1;
    int saved_stdout = -1;
    
    if (unit.redirect)
    {
        saved_stdin = dup(STDIN_FILENO);
        saved_stdout = dup(STDOUT_FILENO);
        
        if (ft_apply_redirections(unit.redirect) == -1)
        {
            if (saved_stdin != -1)
            {
                dup2(saved_stdin, STDIN_FILENO);
                close(saved_stdin);
            }
            if (saved_stdout != -1)
            {
                dup2(saved_stdout, STDOUT_FILENO);
                close(saved_stdout);
            }
            return (500);
        }
    }
    if (ft_is_builtin(unit.args[0]))
        return (ft_execute_builtin(shell, &unit));
    else
        return (ft_shell_command(shell, &unit));
    if (saved_stdin != -1)
    {
        dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdin);
    }
    if (saved_stdout != -1)
    {
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
    }
}