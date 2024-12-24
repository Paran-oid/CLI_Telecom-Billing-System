#include "program.h"
#include "billing.h"
#include "userService.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#if defined(__linux__)
#include <unistd.h>
#elif defined(__WIN32) || defined(__WIN64)
#include <windows.h>
#endif

void exec(void)
{
    unsigned char choice;

    printf("--Telecom Billing System--\n\n");
    while (true)
    {
        struct Customer *user = NULL;
        while (!user)
        {
            auth_menu();
            auth_handler(&user);
        }
        (void)menu();
        (void)scanf(" %c", &choice);
        if (!map_choice(choice))
        {
            break;
        }
        (void)clean();
    }
    (void)printf("--End Program--\n");
}

void menu(void)
{
    (void)printf("Choose one of the following:\n");
    (void)printf("1-Add new record\n");
    (void)printf("2-View list of records\n");
    (void)printf("3-Modify records\n");
    (void)printf("4-View payment\n");
    (void)printf("5-Search records\n");
    (void)printf("6-Delete records\n");
    (void)printf("q-Quit\n");
}

void auth_menu(void)
{
    (void)printf("You must register/login!\n");
    (void)printf("1-Login\n");
    (void)printf("2-Register\n");
}

void auth_handler(struct Customer **user)
{
    unsigned char c;
    if (scanf(" %c", &c) == 1)
    {
        switch (c)
        {
        case '1':
            *user = (struct Customer *)login_user();
            break;
        case '2':
            *user = (struct Customer *)register_user();
            break;
        default:
            *user = NULL;
            break;
        }
    }
}

bool map_choice(unsigned char c)
{
    clean();
    bool leave = true;
    switch (c)
    {
    case '1':
        (void)add_record();
        break;
    case '2':
        (void)view_records();
        break;
    case '3':
        (void)modify_records();
        break;
    case '4':
        (void)view_payments();
        break;
    case '5':
        (void)search_records();
        break;
    case '6':
        (void)delete_records();
        break;
    default:
        leave = false;
    }
    return leave;
}

void clean()
{
#if defined(__linux__) || defined(__APPLE__)
    (void)system("clear");
#elif defined(_WIN32) || defined(_WIN64)
    (void)system("cls");
#else
    // In case of an unsupported platform, you can add a message or default action
    printf("\n[Error] Unsupported platform for clearing the screen.\n");
#endif
}
