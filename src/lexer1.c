#include "../includes/minishell.h"

// int count_elements(t_token *tokens)
// {
//     int count;

//     count = 0;
//     while (tokens)
//     {
//         if (tokens->key == PIPE)
//             count++;
//         tokens = tokens->next;
//     }
//     count++;
//     return (count);
// }

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