#include "userService.h"
#include "fileIO.h"
#include "user.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void *register_user(void) {
  char *username = (char *)malloc(sizeof(char) * (50 + 1));
  char *password = (char *)malloc(sizeof(char) * (20 + 1));

  (void)printf("Enter a username:\n");
  if ((int)scanf("%50s", username) != 1) {
    (void)fprintf(stderr, "Invalid username\n");
    return NULL;
  }
  (void)printf("Enter a password:\n");
  if ((int)scanf("%20s", password) != 1) {
    (void)fprintf(stderr, "Invalid password\n");
    return NULL;
  }

  struct User *user = create_user(username, password);
  char user_str[70] = "";

  (void)snprintf(user_str, sizeof(user_str), "%d", user->id);

  char *item_arr[] = {" ", user->name, " ", user->password, "\n"};

  for (size_t i = 0; i != sizeof(item_arr) / sizeof(item_arr[0]); i++) {
    (void)strcat(user_str, item_arr[i]);
  }

  if (!user) {
    (void)fprintf(stderr, "There was an error creating your account\n");
  }

  (void)file_write(USERS_DIR, user_str);

  return user;
}

void *login_user(void) {
  char username[50];
  char password[20];

  printf("Enter a username:\n");
  if (scanf("%50s", username) != 1) {
    fprintf(stderr, "Invalid username\n");
    return NULL;
  }

  printf("Enter a password:\n");
  if (scanf("%20s", password) != 1) {
    fprintf(stderr, "Invalid password\n");
    return NULL;
  }

  struct User *user = (struct User *)malloc(sizeof(struct User));

  char *found_user = search_in_file(USERS_DIR, USERNAME, username);

  if (!found_user) {
    fprintf(stderr, "Invalid credentials\n");
    return NULL;
  }

  char user_str[100] = "";

  char *id_str = format_from_stream(ID, found_user);

  strcat(user_str, id_str);
  strcat(user_str, " ");
  strcat(user_str, username);
  strcat(user_str, " ");
  strcat(user_str, password);

  if (strcmp(user_str, found_user) != 0) {
    fprintf(stderr, "Wrong credentials, please try again.\n");
    return NULL;
  }

  user->id = atoi(id_str);
  user->name = username;
  user->password = password;

  free(found_user);

  return user;
}

struct User *create_user(char *username, char *password) {
  (void)srand((time_t)time(NULL));
  struct User *user = (struct User *)malloc(sizeof(struct User));

  bool valid_id = false;
  char *user_id_str = (char *)malloc(sizeof(char) * (4 + 1));

  int offset = 0;

  while (!valid_id) {
    user->id = 1 + offset;

    (void)snprintf(user_id_str, 5, "%u", user->id);
    char *found_item = (char *)search_in_file(USERS_DIR, ID, user_id_str);

    if (found_item == NULL) {
      valid_id = true;
    }

    offset += 1;
  }

  user->name = username;
  user->password = password;

  (void)free(user_id_str);

  return user;
}

void destroy_user(struct User *user) {
  (void)free(user->name);
  (void)free(user->password);
  (void)free(user);
}