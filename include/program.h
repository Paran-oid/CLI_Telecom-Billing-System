#pragma once

#include <stdbool.h>

struct Customer;

void exec(void);

void auth_menu(void);
void auth_handler(struct Customer **user);

void menu(void);
bool map_choice(unsigned char c, const char *working_dir);

void clean(void);
