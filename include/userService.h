#pragma once

struct User;

struct User *create_user(char *username, char *password);
void *register_user(void);
void *login_user(void);
void destroy_user(struct User *user);
