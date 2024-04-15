
#include "../includes/minishell.h"

// test that the prev and next node are correctly allocated and that the values match the expected values
void test_list(t_token *tokens) {
    t_token *current = tokens;
    while (current) {
        printf("Current value: %s\n", current->value);

        if (current->prev) {
            printf("Prev value: %s\n", current->prev->value);
        } else {
            printf("Prev is NULL\n");
        }

        if (current->next) {
            printf("Next value: %s\n", current->next->value);
        } else {
            printf("Next is NULL\n");
        }

        current = current->next;
    }
}

void print_commands(t_command *commands)
{
    t_command *current_command = commands;
    int i;

    while (current_command)
    {
        printf("Command: ");
        if (current_command->cmd_name)
        {
            for (i = 0; current_command->cmd_name[i]; i++)
            {
                printf("%s ", current_command->cmd_name[i]);
            }
            printf("\n");
        }

        t_token *current_redirection = current_command->redirections;
        while (current_redirection)
        {
            printf("Redir val: %s\n", current_redirection->value);
            printf("Redir type: %d\n", current_redirection->type);
            current_redirection = current_redirection->next;
        }

        current_command = current_command->next;
    }
}