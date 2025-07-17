/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:53:23 by saincesu          #+#    #+#             */
/*   Updated: 2025/07/15 20:53:32 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int create_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    return (0);
}

pid_t create_child_process(void)
{
    pid_t   pid;
    
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (-1);
    }
    return (pid);
}

void execute_pipeline_command(t_shell *shell, t_parser *parser, int input_fd, int output_fd)
{
    int    exit_code;
    char    *full_path;

    if (input_fd != STDIN_FILENO)
    {
        if (dup2(input_fd, STDIN_FILENO) == -1)
        {
            perror("dup2 input");
            exit(1);
        }
        close(input_fd);
    }
    if (output_fd != STDOUT_FILENO)
    {
        if (dup2(output_fd, STDOUT_FILENO) == -1)
        {
            perror("dup2 output");
            exit(1);
        }
        close(output_fd);
    }
    if (parser->redirect && ft_apply_redirections(parser->redirect) == -1)
        exit(1);
    if (ft_is_builtin(parser->args[0]))
    {
        exit_code = ft_execute_builtin(shell, parser);
        exit(exit_code);
    }
    else
    {
        full_path = ft_search_command_path(parser->args[0]);
        if (!full_path)
        {
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(parser->args[0], 2);
            ft_putstr_fd(": command not found\n", 2);
            exit(127);
        }
        
        execve(full_path, parser->args, shell->env);
        perror("execve");
        exit(126);
    }
}

t_token *create_command_tokens(t_token *start, t_token *end)
{
    t_token *head = NULL;
    t_token *tail = NULL;
    t_token *current = start;
    
    while (current && current != end)
    {
        t_token *new_token = ft_alloc(sizeof(t_token));
        new_token->content = ft_strdup(current->content);
        new_token->type = current->type;
        new_token->flag = current->flag;
        new_token->next = NULL;
        new_token->prev = tail;
        
        if (!head)
            head = new_token;
        else
            tail->next = new_token;
        
        tail = new_token;
        current = current->next;
    }
    
    return (head);
}

t_parser *parse_pipeline_commands(t_shell *shell, int *cmd_count)
{
    t_token *current = shell->args;
    int count = 1;

    while (current)
    {
        if (current->type == PIPE)
            count++;
        current = current->next;
    }
    
    *cmd_count = count;
    t_parser *commands = ft_alloc(sizeof(t_parser) * count);
    
    current = shell->args;
    int cmd_index = 0;
    t_token *cmd_start = current;
    
    // Parse each command
    while (current && cmd_index < count)
    {
        if (current->type == PIPE || current->next == NULL)
        {
            t_token *cmd_end = (current->type == PIPE) ? current : current->next;
            
            // Create a separate token chain for this command
            t_token *cmd_tokens = create_command_tokens(cmd_start, cmd_end);
            
            // Create a temporary shell structure for this command
            t_shell temp_shell = *shell;
            temp_shell.args = cmd_tokens;
            
            // Parse this command unit
            t_parser temp_parsed = {0}; // Initialize with zeros
            commands[cmd_index] = ft_parse_command(&temp_shell, temp_parsed);
            
            // Set up linked list connections
            if (cmd_index > 0)
            {
                commands[cmd_index].prev = &commands[cmd_index - 1];
                commands[cmd_index - 1].next = &commands[cmd_index];
            }
            if (cmd_index == 0)
                commands[cmd_index].prev = NULL;
            
            cmd_index++;
            if (current->next)
                cmd_start = current->next;
        }
        current = current->next;
    }
    
    // Set the last command's next pointer to NULL
    if (count > 0)
        commands[count - 1].next = NULL;
    
    return (commands);
}

// Wait for all child processes and get the exit status of the last one
int wait_for_pipeline(pid_t *pids, int cmd_count)
{
    int status;
    int last_exit_code = 0;
    
    // Wait for all children, but keep track of the last one's exit code
    for (int i = 0; i < cmd_count; i++)
    {
        if (pids[i] > 0)
        {
            waitpid(pids[i], &status, 0);
            if (i == cmd_count - 1) // Last command determines exit code
                last_exit_code = WEXITSTATUS(status);
        }
    }
    
    return (last_exit_code);
}

int ft_multi_command(t_shell *shell, t_parser *parsed)
{
    (void)parsed;
    int cmd_count;
    t_parser *commands = parse_pipeline_commands(shell, &cmd_count);
    
    if (!commands || cmd_count == 0)
        return (1);
    
    pid_t *pids = ft_alloc(sizeof(pid_t) * cmd_count);
    int **pipes = ft_alloc(sizeof(int*) * (cmd_count - 1));
    
    // Create all pipes needed
    for (int i = 0; i < cmd_count - 1; i++)
    {
        pipes[i] = ft_alloc(sizeof(int) * 2);
        if (create_pipe(pipes[i]) == -1)
            return (1);
    }
    
    // Execute each command in the pipeline
    for (int i = 0; i < cmd_count; i++)
    {
        pids[i] = create_child_process();
        
        if (pids[i] == -1)
        {
            // Clean up pipes and return error
            for (int j = 0; j < cmd_count - 1; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            return (1);
        }
        
        if (pids[i] == 0) // Child process
        {
            int input_fd = STDIN_FILENO;
            int output_fd = STDOUT_FILENO;
            
            // Set up input from previous command
            if (i > 0)
                input_fd = pipes[i - 1][0];
            
            // Set up output to next command
            if (i < cmd_count - 1)
                output_fd = pipes[i][1];
            
            // Close all pipe file descriptors in child
            for (int j = 0; j < cmd_count - 1; j++)
            {
                if (j != i - 1 || i == 0) // Don't close input pipe for this command
                    close(pipes[j][0]);
                if (j != i || i == cmd_count - 1) // Don't close output pipe for this command
                    close(pipes[j][1]);
            }
            
            // Execute the command
            execute_pipeline_command(shell, &commands[i], input_fd, output_fd);
        }
    }
    
    // Parent process: close all pipe file descriptors
    for (int i = 0; i < cmd_count - 1; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    
    // Wait for all children and get exit code
    int exit_code = wait_for_pipeline(pids, cmd_count);
    
    return (exit_code);
}