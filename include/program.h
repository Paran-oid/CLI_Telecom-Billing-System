#pragma once

#include <stdbool.h>

struct User;

void exec(void);

void auth_menu(void);
bool auth_handler(struct User **user);

void menu(void);
bool map_choice(const char *working_dir);

void clean(void);
