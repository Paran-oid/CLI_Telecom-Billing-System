#pragma once

struct Customer;

struct Customer *create_user(char *username, char *password);
struct Customer *register_user(void);
struct Customer *login_user(void);
void destroy_user(struct Customer *user);
