#include "../includes/minishell.h"

int count_nodes_between_pipes(t_token *tokens)
{
    int count = 0;
    int total = 0;
    int found_pipe = 0;

    while (tokens)
    {
        if (tokens->key == PIPE)
        {
            if (found_pipe)
            {
                total += count;
            }
            found_pipe = 1;
            return (count);
        }
        else if (found_pipe)
        {
            count++;
        }
        tokens = tokens->next;
    }
    return total;
}

char ***get_commands(t_token *tokens)
{
    int num_commands = 1;
    t_token *temp = tokens;
    while (temp)
    {
        if (temp->key == PIPE)
        {
            num_commands++;
        }
        temp = temp->next;
    }

    char ***commands = malloc((num_commands + 1) * sizeof(char **));
    if (!commands)
    {
        exit(EXIT_FAILURE);
    }

    int i = 0;
    int j = 0;
    commands[i] = malloc((num_commands + 1) * sizeof(char *));
    while (tokens)
    {
        if (tokens->key == PIPE)
        {
            commands[i][j] = NULL;
            i++;
            j = 0;
            commands[i] = malloc((num_commands + 1) * sizeof(char *));
        }
        else
        {
            commands[i][j] = ft_strdup(tokens->value);
            j++;
        }
        tokens = tokens->next;
    }
    commands[i][j] = NULL;
    commands[i + 1] = NULL;

    return commands;
}