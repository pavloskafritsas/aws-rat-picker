#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "aws/client.h"

#include "menu.h"
#include "messages.h"

#define MAX_CLIENT_STR_INPUT_LEN 1

void print_menu(struct ClientList client_list)
{
    printf("%s\n\n", MENU_TITLE);

    printf("0. %s\n", MENU_OPTION_EXIT);

    for (int i = 0; i < client_list.count; i++)
    {
        printf("%i. %s\n", 1 + i, client_list.clients[i].name);
    }
}

int get_index(int min, int max)
{
    int value;

    char input[MAX_CLIENT_STR_INPUT_LEN + 2]; // +1 for newline, +1 for null terminator
    char *endptr;

    if (!fgets(input, sizeof(input), stdin))
    {
        fprintf(stderr, "%s\n", ERROR_INPUT);
        return min - 1;
    }

    // Remove trailing newline if present
    size_t len = strcspn(input, "\n");

    if (input[len] == '\n')
    {
        input[len] = '\0';
    }
    else
    {
        // Input was too long; flush the remaining characters
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
    }

    // Check if input is all digits
    int is_digit = 1;

    for (size_t i = 0; i < strlen(input); ++i)
    {
        if (!isdigit((unsigned char)input[i]))
        {
            is_digit = 0;

            break;
        }
    }

    if (!is_digit)
    {
        printf("%s\n", ERROR_INPUT_NOT_NUMBER);

        return min - 1;
    }

    // Convert to integer
    value = strtol(input, &endptr, 10);

    // Check for valid range
    if (value < min || value > max)
    {
        printf("Enter a number between % d and % d \n", min, max);

        return min - 1;
    }

    return value;
}

struct Client select_client(struct ClientList client_list)
{
    const int min = 0;
    const int max = client_list.count;

    int index = -1;

    do
    {
        printf("\n%s ", MENU_CLIENTS_SELECT);

        index = get_index(min, max) - 1;

        if (index == -1)
        {
            printf("\nBye!\n");

            exit(EXIT_SUCCESS);
        }
    } while (index < min - 1);

    return client_list.clients[index];
}

void print_selected_client_info(Client client)
{
    printf("%s %s\n", PRINT_INFO_CLIENT, client.name);
    printf("%s %s\n", PRINT_INFO_REGION, client.region);
}