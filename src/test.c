
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
        if (current_command->cmd_name)
		{
			printf("Command val: ");
			for (i = 0; current_command->cmd_name[i]; i++)
				printf("%s ", current_command->cmd_name[i]);
			while (current_command->redirections)
			{
				if (current_command->redirections->value != NULL)
					printf("\n\tRedir val: %s Redir type: %d ", current_command->redirections->value, current_command->redirections->type);
				current_command->redirections = current_command->redirections->next;
			}
			printf("\n");
		}
		else
		{
			printf("Command val: NULL ");
			while (current_command->redirections)
			{
				printf("\n\tRedir val: %s Redir type: %d", current_command->redirections->value, current_command->redirections->type);
				current_command->redirections = current_command->redirections->next;
			}
			printf("\n");
		}
        current_command = current_command->next;
    }
}

void print_commands_reverse(t_command *commands)
{
    t_command *current_command = get_last_command(commands);
    int i;

    while (current_command)
    {
        if (current_command->cmd_name)
        {
            printf("Command val: ");
            for (i = 0; current_command->cmd_name[i]; i++)
                printf("%s ", current_command->cmd_name[i]);
            while (current_command->redirections)
            {
                if (current_command->redirections->value != NULL)
                    printf("\n\tRedir val: %s Redir type: %d ", current_command->redirections->value, current_command->redirections->type);
                current_command->redirections = current_command->redirections->next;
            }
            printf("\n");
        }
        else
        {
            printf("Command val: NULL ");
            while (current_command->redirections)
            {
                printf("\n\tRedir val: %s Redir type: %d", current_command->redirections->value, current_command->redirections->type);
                current_command->redirections = current_command->redirections->next;
            }
            printf("\n");
        }
        current_command = current_command->prev;
    }
}