#include "fileIO.h"

#include <stdio.h>

bool file_write(char *path, char *val)
{
    FILE* f = fopen(path, "a");
    if(f == NULL)
    {
        printf("error allocationg memory\n");
        return false;
    }
    fprintf(f, "%s", val);
    fclose(f); 
    return true;
}
void file_read(char *path)
{
    FILE* f = fopen(path, "r");
    if(f == NULL)
    {
        printf("error allocating memory\n");
        return;
    }
    char buffer[255];
    while(fscanf(f, "%s", buffer) != EOF)
    {
        printf("%s\n", buffer);
    }
    fclose(f);
}