#pragma once

#include <stdbool.h>

#define USERS_DIR "../data/users.txt"
#define RECORDS_DIR "../data/users/aziz_records.txt"
#define TEMP_DIR "../data/users/temp.txt"

// GENERAL
bool file_write(const char *path, const char *val);
void file_read(const char *path);

// APP
char *search_transaction_in_file(const char *path, const char *id);
bool replace_transaction_in_file(const char *path, const char *modified_item, bool delete_mode);
char *format_transaction_id_from_stream(const char *input);

// USER
char *search_user_in_file(const char *path, const char *username);
char *format_username_from_stream(const char *input);