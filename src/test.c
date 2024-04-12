
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