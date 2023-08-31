#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "main.h"
#include "discord.h"

int option0, option1, option2;
char webhook[1024];
char message[1024];
char token[1024];

interface_mode_t interface_mode;

int main(int argc, char * argv[])
{
    interface_mode = INTERFACE_TUI;

    while(1)
    {
        switch(interface_mode)
        {
        case INTERFACE_TUI:
            printf("\033[?1049h");
            printf(",------.  ,--.                               ,--. \n|  .-.  \\ `--' ,---.  ,---. ,--,--.,--.--. ,-|  | \n|  |  \\  :,--.(  .-' | .--'' ,-.  ||  .--'' .-. | \n|  '--'  /|  |.-'  `)\\ `--.\\ '-'  ||  |   \\ `-' | \n`-------' `--'`----'  `---' `--`--'`--'    `---'  \n");
            printf("\x1b[1mEnter an option\x1b[0m: \n1. \x1b[4mDiscord token checker\x1b[0m.\n2. \x1b[4mDiscord webhook spammer\x1b[0m.\n3. \x1b[4mExit\x1b[0m.\n");
            printf("</> ");

            if (scanf("%d", &option0) != 1)
            {
                fprintf(stderr, "\x1b[31;1merror:\x1b[0m Number was expected\n");
                printf("\033[?1049l");
                return -1;
            }

            switch(option0)
            {
            case 1:
                printf("\033[2J\x1b[1mHow would you like to check the token(s)?\x1b[0m\n");
                printf("\x1b[1mEnter an option\x1b[0m: \n1. \x1b[4mCheck single token from this interface\x1b[0m.\n");
                printf("</> ");

                if (scanf("%d", &option1) != 1)
                {
                    fprintf(stderr, "\x1b[31;1merror:\x1b[0m Number was expected\n");
                    printf("\033[?1049l");
                    return -1;
                }

                switch(option1)
                {
                case 1:
                    printf("\x1b[1mEnter the token: \x1b[0m\nThe token comes in a format similar to \x1b[4mMTAyNjI1Njg3NTMxNjA1MTk4OQ.Ga8xKS.qG4YMsX2eMe9U5_p0EkAdRAVBM-3x_K2ResB5U\x1b[0m, and can be either a bot token or a regular user token.\n");
                    printf("</> ");

                    if(scanf("%s", &token) != 1)
                    {
                        fprintf(stderr, "\x1b[31;1merror:\x1b[0m String was expected.\n");
                        printf("\033[?1049l");
                        return -1;
                    }

                    getchar();

                    int ret0 = discord_check_token(token);

                    if(ret0 == 200)
                    {
                        printf("\x1b[37;1minfo:\x1b[0m Token is valid!\n");
                    }
                    else if(ret0 == 403)
                    {
                        printf("\x1b[37;1minfo:\x1b[0m Token is locked.\n");
                    }
                    else if(ret0 == 401)
                    {
                        printf("\x1b[37;1minfo:\x1b[0m Token is invalid.\n");
                    }
                    else if(ret0 == 429)
                    {
                        fprintf(stderr, "\x1b[31;1merror:\x1b[0m Rate limited, try again later.\n");
                    }
                    else
                    {
                        fprintf(stderr, "\x1b[31;1merror:\x1b[0m Unknown error.\n");
                    }
                    
                    printf("\x1b[3mPress any key to return to menu\x1b[0m\n"); 
                    getchar();

                    break;
                }
            case 2:
                printf("\033[2J\x1b[1mWhat's the webhook's URL?\x1b[0m\n");
                printf("</> ");

                if (scanf("%s", &webhook) != 1)
                {
                    fprintf(stderr, "\x1b[31;1merror:\x1b[0m URL was expected\n");
                    printf("\033[?1049l");
                    return -1;
                }

                printf("\033[2J\x1b[1mWhat message should the webhook send?\x1b[0m\n");
                printf("</> ");

                if (scanf("%s", &message) != 1)
                {
                    fprintf(stderr, "\x1b[31;1merror:\x1b[0m String was expected\n");
                    printf("\033[?1049l");
                    return -1;
                }

                printf("\033[2J\x1b[1mCurrently spamming message.\x1b[0m\n\x1b[3mPress Ctrl + C to end this process\x1b[0m.\n");

                while (1) 
                {
                    discord_send_webhook(&webhook, &message);
                }

                break;
            case 3:
                printf("\033[?1049l");
                return 0;
            }

            printf("\033[?1049l");
        }
    }
    
    
    return 0;
}
