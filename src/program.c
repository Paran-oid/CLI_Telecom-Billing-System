#include "program.h"
#include "billing.h"
#include "userService.h"
#include "customer.h"
#include "fileIO.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#if defined(__linux__)
#include <unistd.h>
#elif defined(__WIN32) || defined(__WIN64)
#include <windows.h>
#endif

void exec(void)
{
    printf("--Telecom Billing System--\n\n");

    struct Customer *user = NULL;
    char *working_dir = NULL;
    unsigned char choice;

    while (true)
    {
        while (!user)
        {
            (void)auth_menu();
            (void)auth_handler(&user);
        }

        if (!working_dir)
        {
            working_dir = (char *)form_working_dir(user);
        }

        (void)menu();
        (void)scanf(" %c", &choice);
        if (!map_choice(choice, working_dir))
        {
            free(working_dir);
            break;
        }
        (void)clean();
    }
    printf("--Thank you for trying my program!\n");
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

bool map_choice(unsigned char c, const char *working_dir)
{
    clean();
    bool stay = true;
    switch (c)
    {
    case '1':
        (void)add_record(working_dir);
        break;
    case '2':
        (void)view_records(working_dir);
        break;
    case '3':
        (void)modify_records(working_dir);
        break;
    case '4':
        (void)view_payments(working_dir);
        break;
    case '5':
        (void)search_records(working_dir);
        break;
    case '6':
        (void)delete_records(working_dir);
        break;
    case 'q':
        stay = false;
        break;
    default:
        break;
    }
    return stay;
}

void clean()
{
#if defined(__linux__) || defined(__APPLE__)
    (void)system("clear");
#elif defined(_WIN32) || defined(_WIN64)
    (void)system("cls");
#else
    // In case of an unsupported platform, you can add a message or default action
    fprintf(stderr, "\n[Error] Unsupported platform for clearing the screen.\n");
#endif
}