#pragma once

#include <stdbool.h>

#define RECORDS_DIR "../data/users/aziz_records.txt"
#define TEMP_DIR "../data/users/temp.txt"

// GENERAL

bool file_write(const char *path, const char *val);
void file_read(const char *path);

// APP

char *search_item_file(const char *path, const char *id);
bool replace_item_file(const char *path, const char *modified_item);

char *format_id(const char *buffer);