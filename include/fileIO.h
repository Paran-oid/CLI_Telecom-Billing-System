#pragma once

#include <stdbool.h>

#define TEMPLATE_RECORDS_DIR "../data/users/"
#define USERS_DIR "../data/users.txt"
#define TEMP_DIR "../data/users/temp.txt"

enum formatType
{
    ID,
    USERNAME,
    PASSWORD
};

enum itemType
{
    USER,
    TRANSACTION
};

struct Customer;

char *form_working_dir(struct Customer *user);

bool file_write(const char *path, const char *val);
void file_read(const char *path);

char *search_in_file(const char *path, enum formatType format, const char *info);
bool replace_in_file(const char *path, const char *modified_item, bool delete_mode);
char *format_from_stream(enum formatType format, const char *stream);
