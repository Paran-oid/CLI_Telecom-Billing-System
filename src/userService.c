#include "userService.h"
#include "customer.h"
#include "fileIO.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Customer *register_user(void)
{
    char *username = (char *)malloc(sizeof(char) * (50 + 1));
    char *password = (char *)malloc(sizeof(char) * (20 + 1));

    printf("enter a username:\n");
    if (scanf("%50s", username) == 1)
    {
        printf("entered a password:\n");
        if (scanf("%20s", password) == 1)
        {
            struct Customer *user;
            user = create_user(username, password);
            char user_str[70] = "";
            snprintf(user_str, sizeof(user_str), "%d", user->id);
            strcat(user_str, " ");
            strcat(user_str, user->name);
            strcat(user_str, " ");
            strcat(user_str, user->password);

            if (user)
            {
                file_write(USERS_DIR, user_str);
                return user;
            }
        }
    }
}
struct Customer *login_user(void)
{
    char username[50];
    char password[20];
    printf("enter a username:\n");
    if (scanf("%50s", username) == 1)
    {
        printf("entered a password:\n");
        if (scanf("%20s", password) == 1)
        {
            char user_str[70];
            struct Customer *user;
            // user_str = search_item_file(username, password);
            char user_str[70];
            strcat(user_str, username);
            strcat(user_str, " ");
            strcat(user_str, password);

            if (user)
            {
                file_write(USERS_DIR, user_str);
                return user;
            }
        }
    }
}

struct Customer *create_user(char *username, char *password)
{
    srand(time(NULL));
    struct Customer *user = (struct Customer *)malloc(sizeof(struct Customer));
    user->id = 1 + (rand() % (1000));
    user->name = username;
    user->password = password;

    return user;
}

void destroy_user(struct Customer *user)
{
    free(user->name);
    free(user->password);
    free(user);
}