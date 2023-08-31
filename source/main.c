#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

#include "main.h"

interface_mode_t interface_mode;

int main(int argc, char * argv[])
{
    interface_mode = INTERFACE_TUI;

    switch(interface_mode)
    {
    case INTERFACE_TUI:
        int option0 = -1;

        printf("\033[?1049h");
        printf(",------.  ,--.                               ,--. \n|  .-.  \\ `--' ,---.  ,---. ,--,--.,--.--. ,-|  | \n|  |  \\  :,--.(  .-' | .--'' ,-.  ||  .--'' .-. | \n|  '--'  /|  |.-'  `)\\ `--.\\ '-'  ||  |   \\ `-' | \n`-------' `--'`----'  `---' `--`--'`--'    `---'  \n");
        printf("\x1b[1mEnter an option\x1b[0m: \n1. \x1b[4mDiscord token checker\x1b[0m.\n2. \x1b[4mDiscord webhook spammer\x1b[0m.\n");
        printf("</> ");

        if (scanf("%d", &option0) != 1)
        {
            fprintf(stderr, "error: number was expected\n");
            return -1;
        }

        switch(option0)
        {
        case 1:
            int option1;
            printf("\033[2J\x1b[1mHow would you like to check the token(s)?\x1b[0m\n");
            printf("\x1b[1mEnter an option\x1b[0m: \n1. \x1b[4mCheck single token from this interface\x1b[0m.\n");
            printf("</> ");

            if (scanf("%d", &option1) != 1)
            {
                fprintf(stderr, "error: number was expected\n");
                return -1;
            }

            switch(option1)
            {
            case 1:
                char token[1024];
                printf("\033[2J\x1b[1mEnter the token: \x1b[0m");

                if(scanf("%s", &token) != 1)
                {
                    fprintf(stderr, "error: string was expected\n");
                    return -1;
                }

                
                break;
            }
        }

        printf("\033[?1049l");
    }
    
    return 0;
}