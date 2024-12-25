#include "program.h"
#include "billing.h"
#include "userService.h"
#include "user.h"
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

    struct User *user = NULL;
    char *working_dir = NULL;
    bool run = true;

    while (run)
    {
        while (!user && run)
        {
            // give user choice to login or register
            run = (bool)auth_handler(&user);
            if (!run)
            {
                continue;
            }
        }

        if (user)
        {
            if (!working_dir)
            {
                working_dir = (char *)form_working_dir(user);
            }

            (void)clean();
            // user's choice will be mapped here so he can do the action he wants
            if (!(bool)map_choice(working_dir))
            {
                user = NULL;
                (void)free(working_dir);
            }
            (void)clean();
        }
    }
    (void)printf("--Thank you for trying my program!\n");
}

void auth_menu(void)
{
    (void)printf("You must register/login!\n");
    (void)printf("1-Login\n");
    (void)printf("2-Register\n");
    (void)printf("q-Quit\n");
}

bool auth_handler(struct User **user)
{
    (void)auth_menu();

    bool stay = true;
    bool valid_input = false;
    unsigned char choice;

    while (!valid_input)
    {
        if ((int)scanf(" %c", &choice) != 1)
        {
            printf("Please enter a valid choice\n");
            // empty input buffer
            while (getchar() != '\n')
                ;
        }
        valid_input = true;
    }

    switch (choice)
    {
    case '1':
        *user = (struct User *)login_user();
        break;
    case '2':
        *user = (struct User *)register_user();
        break;
    case 'q':
        stay = false;
        break;
    default:
        break;
    }
    return stay;
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

bool map_choice(const char *working_dir)
{
    menu();
    bool valid_input = false;
    unsigned char choice;

    while (!valid_input)
    {
        if ((int)scanf(" %c", &choice) != 1)
        {
            printf("Please enter a valid choice\n");
            // empty input buffer
            while (getchar() != '\n')
                ;
        }
        valid_input = true;
    }

    bool stay = true;
    switch (choice)
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