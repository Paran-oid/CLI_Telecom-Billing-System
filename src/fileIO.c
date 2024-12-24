#include "fileIO.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// GENERAL
bool file_write(const char *path, const char *val)
{
    assert(path);
    assert(val);

    FILE *f = (FILE *)fopen(path, "a");
    if (f == NULL)
    {
        (void)printf("error opening file\n");
        return false;
    }
    if ((int)fprintf(f, "%s", val) < 0)
    {
        (void)fclose(f);
        (void)printf("error writing to file\n");
        return false;
    }
    (void)fclose(f);
    return true;
}

void file_read(const char *path)
{
    assert(path);

    FILE *f = (FILE *)fopen(path, "r");
    if (f == NULL)
    {
        (void)printf("error opening file/s\n");
        return;
    }
    char buffer[255];
    while ((char *)fgets(buffer, sizeof(buffer), f))
    {
        (void)printf("%s\n", buffer);
    }
    (void)fclose(f);
}

// TRANSACTION SECTION
char *search_transaction_in_file(const char *path, const char *id)
{
    assert(id);
    assert(path);

    FILE *f = (FILE *)fopen(path, "r");

    if (f == NULL)
    {
        (void)printf("error opening file/s\n");
        return NULL;
    }

    bool found = false;

    char buffer[255];

    while ((char *)fgets(buffer, sizeof(buffer), f))
    {
        char *found_id = (char *)format_id(buffer);
        if (found_id == NULL)
        {
            continue;
        }
        if ((int)strcmp(found_id, id) == 0)
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        char *buffer_copy = (char *)malloc(sizeof(char) * (sizeof(buffer) + 1));
        (void)strcpy(buffer_copy, buffer);
        (void)fclose(f);
        return buffer_copy;
    }

    (void)fclose(f);
    return NULL;
}

bool replace_transaction_in_file(const char *path, const char *modified_item, bool delete_mode)
{
    assert(path);
    assert(modified_item);

    FILE *f_orig = (FILE *)fopen(path, "r");
    FILE *f_copy = (FILE *)fopen(TEMP_DIR, "w");

    if (f_orig == NULL || f_copy == NULL)
    {
        (void)printf("error opening file/s\n");
        return false;
    }

    char buffer[255];
    char *specific_id = (char *)format_id(modified_item);
    bool result = false;

    if (!delete_mode)
    {
        while ((char *)fgets(buffer, sizeof(buffer), f_orig))
        {
            char *found_id = (char *)format_id(buffer);
            if (strcmp(found_id, specific_id) == 0)
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
    }
    (void)fclose(f_orig);
    (void)fclose(f_copy);

    f_orig = (FILE *)fopen(path, "w");
    f_copy = (FILE *)fopen(TEMP_DIR, "r");

    if (f_orig == NULL || f_copy == NULL)
    {
        (void)printf("error allocationg memory\n");
        return false;
    }

    while (fgets(buffer, sizeof(buffer), f_copy))
    {
        (void)fprintf(f_orig, "%s", buffer);
    }

    (void)fclose(f_orig);
    (void)fclose(f_copy);

    (void)remove(TEMP_DIR);

    return result;
}

char *format_transaction_from_id(const char *buffer)
{
    {
        assert(buffer);

        size_t index;
        char *address_space;
        address_space = strchr(buffer, ' ');

        index = (int)(address_space - buffer);
        char *found_id = (char *)malloc(sizeof(char) * (3 + 1));

        for (size_t i = 0; i < index; i++)
        {
            found_id[i] = buffer[i];
        }
        found_id[index] = '\0';
        return found_id;
    }
}

// AUTH SECTION

char *search_user_in_file(const char *path, const char *username)
{
    FILE *f = fopen(USERS_DIR, "r");

    bool found = false;
    char *found_user = malloc(sizeof(char) * (255 + 1));
    char buffer[255];
    while (fgets(buffer, sizeof(buffer), f))
    {
        const char *received_username = (char *)format_username_from_stream(buffer);
        if ((int)strcmp(received_username, buffer) == 0)
        {
            (void)memcpy(found_user, buffer, strlen(buffer));
            found = true;
            break;
        }
    }

    return found ? found_user : NULL;
}

char *format_username_from_stream(const char *input)
{
    char *pos = strchr(input, ' ');

    if (!pos)
    {
        return NULL;
    }

    size_t start = pos - input;
    size_t curr = pos - input;

    while (input[curr])
    {
        curr++;
    }

    char *username = (char *)malloc(sizeof(char) * (50 + 1));
    memcpy(username, input + start, curr - start);

    return username;
}

// MIX
