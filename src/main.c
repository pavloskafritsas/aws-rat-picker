#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "aws/config.h"
#include "aws/rat.h"

#include "menu.h"
#include "logo.h"

int main(int argc, const char *argv[])
{
    Client selected_client;

    const char *aws_rat_path = get_aws_rat_path();

    const struct ClientList client_list = get_client_list();

    print_logo();

    do
    {
        print_menu(client_list);

        selected_client = select_client(client_list);

        start_aws_rat(aws_rat_path, selected_client);

    } while (wait(NULL) > 0);

    free_client_list(client_list);

    return EXIT_SUCCESS;
}