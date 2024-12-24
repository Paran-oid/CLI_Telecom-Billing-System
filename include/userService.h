#pragma once

struct Customer;

struct Customer *create_user(char *username, char *password);
void *register_user(void);
void *login_user(void);
void destroy_user(struct Customer *user);
