#pragma once

#include <stdbool.h>

#define USERS_DIR "../data/users.txt"
#define RECORDS_DIR "../data/users/aziz_records.txt"
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

bool file_write(const char *path, const char *val);
void file_read(const char *path);

char *search_in_file(const char *path, enum formatType format, const char *info, enum itemType item_type);
bool replace_in_file(const char *path, const char *modified_item, enum itemType item_type, bool delete_mode);
char *format_from_stream(enum formatType format, const char *stream);
