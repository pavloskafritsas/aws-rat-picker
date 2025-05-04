#include <stdio.h>
#include <unistd.h>

#include "logo.h"
#include "terminal.h"

#define TYPE_DELAY 3000

#define LOGO_DURATION 1000000 * 2

void type_line(const char *line, const int delay, const char *color)
{
    printf(color);

    while (*line)
    {
        putchar(*line++);
        fflush(stdout);
        usleep(delay); // 30ms delay between characters
    }

    printf(ANSI_RESET);
}

void print_logo()
{
    printf(ANSI_CLEAR);

    const char *color_logo_aws = ANSI_COLOR_B_BLUE;
    const char *color_logo_rat = ANSI_COLOR_B_WHITE;
    const char *color_logo_pk = ANSI_COLOR_B_GREEN;
    const char *color_accent = ANSI_COLOR_B_YELLOW;

    const int delay_logo_aws = TYPE_DELAY / 2.5;
    const int delay_logo_rat = TYPE_DELAY;
    const int delay_logo_pk = 0;

    type_line("█████╗  ██╗    ██╗███████╗\n", delay_logo_aws, color_logo_aws);
    type_line("██╔══██╗██║    ██║██╔════╝\n", delay_logo_aws, color_logo_aws);
    type_line("███████║██║ █╗ ██║███████╗\n", delay_logo_aws, color_logo_aws);
    type_line("██╔══██║██║███╗██║╚════██║\n", delay_logo_aws, color_logo_aws);
    type_line("██║  ██║╚███╔███╔╝███████║\n", delay_logo_aws, color_logo_aws);
    type_line("╚═╝  ╚═╝ ╚══╝╚══╝ ╚══════╝\n", delay_logo_aws, color_logo_aws);

    printf("\n");

    type_line("                           ██████╗     █████╗ ████████╗\n", delay_logo_rat, color_logo_rat);
    type_line("                           ██╔══██╗   ██╔══██╗╚══██╔══╝\n", delay_logo_rat, color_logo_rat);
    type_line("                           ██████╔╝   ███████║   ██║   \n", delay_logo_rat, color_logo_rat);
    type_line("                           ██║  ██║██╗██║  ██║██╗██║██╗\n", delay_logo_rat, color_logo_rat);
    type_line("                           ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═╝╚═╝╚═╝", delay_logo_rat, color_logo_rat);
    type_line(" (picker)\n", delay_logo_rat, color_accent);

    type_line("                                                                             ██╗  ██╗\n", delay_logo_pk, color_logo_pk);
    type_line("                                                                    ██████╗  ██║ ██╔╝\n", delay_logo_pk, color_logo_pk);
    type_line("                                                                    ██╔══██╗ █████╔╝\n", delay_logo_pk, color_logo_pk);
    type_line("                                                                    ██████╔╝ ██╔═██╗\n", delay_logo_pk, color_logo_pk);
    type_line("                                                                    ██╔═══╝  ██║  ██╗\n", delay_logo_pk, color_logo_pk);
    type_line("                                                                    ██║      ╚═╝  ╚═╝\n", delay_logo_pk, color_logo_pk);

    type_line("                                                               (by)", delay_logo_pk, color_accent);

    type_line(" ╚═╝              \n", delay_logo_pk, color_logo_pk);

    usleep(LOGO_DURATION);

    printf(ANSI_CLEAR);
}
