#include "fileIO.h"
#include "user.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sys/stat.h>
#include <sys/types.h>

char *form_working_dir(struct User *user)
{
    assert(user);
    const size_t MAX_SIZE = 400;

    char *wd = (char *)calloc((MAX_SIZE + 1), sizeof(char));
    // + 4 for .txt and /
    if ((size_t)strlen(TEMPLATE_RECORDS_DIR) + (size_t)strlen(user->name) + 4 < MAX_SIZE)
    {
        (void)strncat(wd, TEMPLATE_RECORDS_DIR, MAX_SIZE - (size_t)strlen(wd));
        (void)strncat(wd, user->name, MAX_SIZE - (size_t)strlen(wd));
        struct stat st = {0};

        if ((int)stat(wd, &st) == -1)
        {
            if ((int)mkdir(wd, 0700) != 0)
            {
                (void)fprintf(stderr, "Erorr creating directory\n");
                (void)free(wd);
                return NULL;
            }
        }

        (void)strncat(wd, "/records.txt", MAX_SIZE - (size_t)strlen(wd));
        return wd;
    }
    else
    {
        fprintf(stderr, "Error: Combined length of TEMPLATE_RECORDS_DIR and user name exceeds limit.\n");
        free(wd);
        return NULL;
    }
}

bool file_write(const char *path, const char *val)
{
    assert(path);
    assert(val);

    FILE *f = fopen(path, "a");
    if (f == NULL)
    {
        fprintf(stderr, "Error opening file\n");
        return false;
    }

    if (fprintf(f, "%s", val) < 0)
    {
        fclose(f);
        fprintf(stderr, "Error writing to file\n");
        return false;
    }

    fclose(f);
    return true;
}

void file_read(const char *path)
{
    assert(path);

    FILE *f = fopen(path, "r");

    if (f == NULL)
    {
        fprintf(stderr, "Error opening file/s\n");
        return;
    }
    char buffer[255];

    while (fgets(buffer, sizeof(buffer), f))
    {
        printf("%s\n", buffer);
    }
    fclose(f);
}

char *search_in_file(const char *path, enum formatType format, const char *info)
{
    assert(info);
    assert(path);

    FILE *f = fopen(path, "r");

    if (f == NULL)
    {
        fprintf(stderr, "Error opening file/s\n");
        return NULL;
    }

    bool found = false;

    char buffer[255];

    while (fgets(buffer, sizeof(buffer), f))
    {
        char *found_item = format_from_stream(format, buffer);
        if (strcmp(found_item, info) == 0)
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        size_t len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }
        char *buffer_copy = malloc(strlen(buffer) + 1);

        if (!buffer_copy)
        {
            fprintf(stderr, "There was an error processing your transaction's string\n");
            return NULL;
        }

        (void)strcpy(buffer_copy, buffer);
        (void)fclose(f);
        return buffer_copy;
    }

    fclose(f);
    return NULL;
}

bool replace_in_file(const char *path, const char *modified_item, bool delete_mode)
{
    assert(path);
    assert(modified_item);

    FILE *f_orig = (FILE *)fopen(path, "r");
    FILE *f_copy = (FILE *)fopen(TEMP_DIR, "w");

    if (f_orig == NULL || f_copy == NULL)
    {
        fprintf(stderr, "Error opening file/s\n");
        return false;
    }

    char buffer[255];
    char *specific_id = (char *)format_from_stream(ID, modified_item);
    bool result = false;

    while ((char *)fgets(buffer, sizeof(buffer), f_orig))
    {
        char *found_id = (char *)format_from_stream(ID, buffer);
        if ((int)strcmp(found_id, specific_id) == 0)
        {
            if (!delete_mode)
            {
                (void)fprintf(f_copy, "%s", modified_item);
            }
            result = true;
            continue;
        }
        (void)fprintf(f_copy, "%s", buffer);
    }
    (void)fclose(f_orig);
    (void)fclose(f_copy);

    f_orig = (FILE *)fopen(path, "w");
    f_copy = (FILE *)fopen(TEMP_DIR, "r");

    if (f_orig == NULL || f_copy == NULL)
    {
        fprintf(stderr, "Error allocating memory\n");
        return false;
    }

    while ((char *)fgets(buffer, sizeof(buffer), f_copy))
    {
        (void)fprintf(f_orig, "%s", buffer);
    }

    (void)fclose(f_orig);
    (void)fclose(f_copy);

    (void)remove(TEMP_DIR);

    return result;
}

char *format_from_stream(enum formatType format, const char *stream)
{
    if (stream == NULL)
    {
        return NULL;
    }

    if (format == USERNAME)
    {
        char *ptr_fspace = strchr(stream, ' ');

        if (!ptr_fspace)
        {
            return NULL;
        }

        size_t start = ptr_fspace - stream + 1;
        size_t curr = ptr_fspace - stream + 1;

        while (stream[curr] != ' ')
        {
            curr++;
        }

        char *username = malloc(51);
        memcpy(username, stream + start, curr - start);
        username[curr - start] = '\0';

        return username;
    }

    else if (format == ID)
    {
        char *ptr_fspace = strchr(stream, ' ');

        if (!ptr_fspace)
        {
            fprintf(stderr, "Invalid stream\n");
            return NULL;
        }

        size_t pos_fspace = ptr_fspace - stream;
        char *found_id = malloc(5);

        for (size_t i = 0; i < pos_fspace; i++)
        {
            found_id[i] = stream[i];
        }
        found_id[pos_fspace] = '\0';
        return found_id;
    }

    else
    {
        fprintf(stderr, "Invalid stream\n");
        return NULL;
    }
}