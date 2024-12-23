#include "fileIO.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool file_write(const char *path, const char *val)
{
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
    FILE *f = (FILE *)fopen(path, "r");
    if (f == NULL)
    {
        (void)printf("error allocating memory\n");
        return;
    }
    char buffer[255];
    while ((char *)fgets(buffer, sizeof(buffer), f))
    {
        (void)printf("%s\n", buffer);
    }
    (void)fclose(f);
}

char *search_item_file(const char *path, const char *id)
{
    FILE *f = (FILE *)fopen(path, "r");

    if (f == NULL)
    {
        (void)printf("error allocationg memory\n");
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
        strcpy(buffer_copy, buffer);
        fclose(f);
        return buffer_copy;
    }

    (void)fclose(f);
    return NULL;
}

bool replace_item_file(const char *path, const char *modified_item)
{
    FILE *f_orig = (FILE *)fopen(path, "r");
    FILE *f_copy = (FILE *)fopen(TEMP_DIR, "w");

    if (f_orig == NULL || f_copy == NULL)
    {
        (void)printf("error allocationg memory\n");
        return false;
    }

    char buffer[255];
    char *specific_id = (char *)format_id(modified_item);
    bool result = false;

    while ((char *)fgets(buffer, sizeof(buffer), f_orig))
    {
        char *found_id = (char *)format_id(buffer);
        if (strcmp(found_id, specific_id) == 0)
        {
            (void)fprintf(f_copy, "%s", modified_item);
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

char *format_id(const char *buffer)
{
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