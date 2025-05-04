#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

#include "aws/config.h"
#include "aws/rat.h"

#include "menu.h"
#include "messages.h"
#include "terminal.h"

void start_aws_rat(const char *aws_rat_path, Client client)
{
    const pid_t child_pid = fork();

    if (child_pid == 0)
    {
        printf(ANSI_CLEAR);

        print_selected_client_info(client);

        // Prepare environment variables
        // Last envp param must be NULL terminated
        char *exec_envp[3] = {NULL, NULL, NULL};

        printf("\n%s\n\n", EXEC_AWS_RAT);

        if (
            asprintf(
                &exec_envp[0],
                "%s=%s",
                VAR_AWS_RAT_PROFILE,
                client.name) == -1 ||
            asprintf(
                &exec_envp[1],
                "%s=%s",
                VAR_AWS_RAT_REGION,
                client.region) == -1)
        {
            fprintf(stderr, "%s\n", ERROR_MEMORY);

            exit(EXIT_FAILURE);
        }

        const char *exec_argv[] = {aws_rat_path, NULL};

        execve(aws_rat_path, (char *const *)exec_argv, exec_envp);

        free(exec_envp[0]);
        exec_envp[0] = NULL;

        free(exec_envp[1]);
        exec_envp[1] = NULL;
    }
    else if (child_pid < 0)
    {
        fprintf(stderr, "%s\n", ERROR_FORK);

        exit(EXIT_FAILURE);
    }
}
