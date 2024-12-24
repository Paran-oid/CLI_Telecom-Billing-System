#include "userService.h"
#include "customer.h"
#include "fileIO.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void *register_user(void)
{
    char *username = (char *)malloc(sizeof(char) * (50 + 1));
    char *password = (char *)malloc(sizeof(char) * (20 + 1));

    (void)printf("enter a username:\n");
    if ((int)scanf("%50s", username) != 1)
    {
        (void)printf("invalid username\n");
        return NULL;
    }
    (void)printf("entered a password:\n");
    if ((int)scanf("%20s", password) != 1)
    {
        (void)printf("Invalid password\n");
        return NULL;
    }

    struct Customer *user;
    user = (struct Customer *)create_user(username, password);
    char user_str[70] = "";
    (void)snprintf(user_str, sizeof(user_str), "%d", user->id);
    (void)strcat(user_str, " ");
    (void)strcat(user_str, user->name);
    (void)strcat(user_str, " ");
    (void)strcat(user_str, user->password);

    if (!user)
    {
        (void)printf("there was an error creating your account\n");
    }

    (void)file_write(USERS_DIR, user_str);
    return user;
}
void *login_user(void)
{
    char id_str[4];
    char username[50];
    char password[20];
    (void)printf("enter a username:\n");
    if ((int)scanf("%50s", username) != 1)
    {
        (void)printf("invalid username\n");
        return NULL;
    }

    (void)printf("entered a password:\n");
    if ((int)scanf("%20s", password) != 1)
    {
        (void)printf("invalid password\n");
    }

    struct Customer *user = (struct Customer *)malloc(sizeof(struct Customer));

    char *user_str = search_user_in_file(USERS_DIR, username);

    if (!user)
    {
        (void)printf("Invalid credentials\n");
    }

    // get user id
    snprintf(id_str, sizeof(id_str), "%d", )

        (void) strcat(user_str, );
    (void)strcat(user_str, username);
    (void)strcat(user_str, " ");
    (void)strcat(user_str, password);

    if (!user)
    {
        (void)printf("Sorry we couldn't log you in :( \n");
    }

    if (strcmp())

        return user;
}

struct Customer *create_user(char *username, char *password)
{
    (void)srand(time(NULL));
    struct Customer *user = (struct Customer *)malloc(sizeof(struct Customer));
    user->id = 1 + ((int)rand() % (1000));
    user->name = username;
    user->password = password;

    return user;
}

void destroy_user(struct Customer *user)
{
    (void)free(user->name);
    (void)free(user->password);
    (void)free(user);
}