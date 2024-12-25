#include "fileIO.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

char *search_in_file(const char *path, enum formatType format, const char *info, enum itemType item_type)
{
    assert(info);
    assert(path);
    assert(item_type);

    if (item_type == TRANSACTION)
    {
        if (format != ID)
        {
            (void)printf("invalid format\n");
            return NULL;
        }

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
            char *found_id = (char *)format_from_stream(ID, buffer);
            if (found_id == NULL)
            {
                continue;
            }
            if ((int)strcmp(found_id, info) == 0)
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
    else if (item_type == USER)
    {
        if (format != USERNAME)
        {
            (void)printf("invalid format\n");
            return NULL;
        }

        FILE *f = fopen(USERS_DIR, "r");

        bool found = false;
        char *found_user = malloc(sizeof(char) * (255 + 1));
        char buffer[255];
        while (fgets(buffer, sizeof(buffer), f))
        {
            const char *received_username = (char *)format_from_stream(USERNAME, buffer);
            if ((int)strcmp(received_username, buffer) == 0)
            {
                (void)memcpy(found_user, buffer, strlen(buffer));
                found = true;
                break;
            }
        }
        return found ? found_user : NULL;
    }
    else
    {
        printf("invalid data\n");
        return NULL;
    }
}

bool replace_in_file(const char *path, const char *modified_item, enum itemType item_type, bool delete_mode)
{
    assert(path);
    assert(modified_item);
    assert(item_type);
    assert(delete_mode);
    if (item_type == TRANSACTION)
    {

        FILE *f_orig = (FILE *)fopen(path, "r");
        FILE *f_copy = (FILE *)fopen(TEMP_DIR, "w");

        if (f_orig == NULL || f_copy == NULL)
        {
            (void)printf("error opening file/s\n");
            return false;
        }

        char buffer[255];
        char *specific_id = (char *)format_from_stream(ID, modified_item);
        bool result = false;

        if (!delete_mode)
        {
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
    else
    {
        printf("invalid input\n");
        return NULL;
    }
}

char *format_from_stream(enum formatType format, const char *stream)
{
    assert(stream);
    assert(format);

    if (format == USERNAME)
    {
        char *pos = strchr(stream, ' ');

        if (!pos)
        {
            return NULL;
        }

        size_t start = pos - stream;
        size_t curr = pos - stream;

        while (stream[curr])
        {
            curr++;
        }

        char *username = (char *)malloc(sizeof(char) * (50 + 1));
        memcpy(username, stream + start, curr - start);

        return username;
    }
    else if (format == ID)
    {
        size_t index;
        char *address_space;
        address_space = strchr(stream, ' ');

        index = (int)(address_space - stream);
        char *found_id = (char *)malloc(sizeof(char) * (3 + 1));

        for (size_t i = 0; i < index; i++)
        {
            found_id[i] = stream[i];
        }
        found_id[index] = '\0';
        return found_id;
    }
    else
    {
        printf("invalid stream\n");
        return NULL;
    }
}