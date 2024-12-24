#pragma once

#include <stdbool.h>

struct Customer;

void auth_menu(void);
void auth_handler(struct Customer **user);

bool map_choice(unsigned char c);
void menu(void);
void exec(void);
void clean(void);
