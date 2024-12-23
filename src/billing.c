#include "billing.h"
#include "record.h"
#include "fileIO.h"
#include "program.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#if defined(__linux__)
#include <unistd.h>
#elif defined(__WIN32) || defined(__WIN64)
#include <windows.h>
#endif

const char *types[] = {"SMR", "CAR", "DTU", "SUB", "TAX", "PAY"};
size_t n = sizeof(types) / sizeof(types[0]);

void display_types(void)
{
    for (size_t i = 0; i < n; i++)
    {
        (void)printf("%s ", types[i]);
    }
    (void)printf("\n");
}

void add_record(void)
{
    (void)srand(time(NULL));

    char output[100];
    struct Record rec;
    bool success = false;

    char rec_id_str[3];
    char rec_value_str[10];

    rec.id = 1 + ((int)rand() % (100));

    (void)snprintf(rec_id_str, sizeof(rec_id_str), "%d", rec.id);
    (void)strcat(output, rec_id_str);

    (void)printf("Enter value\n");
    if (scanf("%f", &rec.val) == 1)
    {
        (void)snprintf(rec_value_str, sizeof(rec_value_str), "%.2f", rec.val);
        (void)strcat(output, " ");
        (void)strcat(output, rec_value_str);

        char input_type[3];
        (void)printf("Enter one of the following types:\n");
        display_types();

        if (((int)scanf("%s", input_type) == 1))
        {
            for (size_t i = 0; i < n; i++)
            {
                if ((int)strcmp(input_type, types[i]) == 0)
                {
                    (void)strcat(output, " ");
                    (void)strcat(output, input_type);
                    (void)strcat(output, "\n");
                    rec.type = i;
                    success = true;
                    break;
                }
                else
                {
                    (void)printf("Invalid type, please try again later\n");
                }
            }
        }
    }

    if (success)
    {
        (void)printf("entered to success section \n");
        if ((bool)file_write(RECORDS_DIR, output))
        {
            (void)printf("Successfully added record!\n");
        }
        else
        {
            (void)printf("There was an error adding the record\n");
        }
    }
    else
    {
        (void)printf("Please verify your inputs next time\n");
    }
}
void view_records(void)
{
    char temp;
    (void)file_read(RECORDS_DIR);
    (void)printf("enter anything to continue...\n");
    (void)scanf(" %c", &temp);
}
void modify_records(void)
{
    int transc_id;
    char transc_id_str[100];
    char *found_item;

    (void)printf("enter item ID\n");
    if ((int)scanf(" %d", &transc_id) == 1)
    {
        (void)snprintf(transc_id_str, sizeof(transc_id), "%d", transc_id);
        found_item = (char *)search_item_file(RECORDS_DIR, transc_id_str);
        if (!(found_item == NULL))
        {
            float new_item_val = 0.00f;
            char new_item_val_str[50];
            char new_item_type[3];

            (void)printf("enter new value\n");
            (void)scanf("%f", &new_item_val);
            (void)snprintf(new_item_val_str, sizeof(new_item_val_str), "%.2f", new_item_val);
            (void)printf("enter new type (must be one of these)\n");
            display_types();
            if (((int)scanf("%3s", new_item_type) == 1))
            {
                bool found = false;
                while (!found)
                {
                    for (size_t i = 0; i < n; i++)
                    {
                        if (strcmp(types[i], new_item_type) == 0)
                        {
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        printf("Couldn't find item type :/\n Please enter a valid type\n");
                        (void)scanf("%3s", new_item_type);
                    }
                }

                (void)clean();
                char modified_transc[150];
                char *building_strs[] =
                    {
                        transc_id_str,
                        " ",
                        new_item_val_str,
                        " ",
                        new_item_type,
                        "\n",
                        NULL};
                for (size_t i = 0; building_strs[i] != NULL; i++)
                {
                    (void)strcat(modified_transc, building_strs[i]);
                }

                if ((bool)replace_item_file(RECORDS_DIR, modified_transc))
                {
                    (void)printf("success!\n");
                    (void)sleep(2);
                }

                (void)free(found_item);
            }
        }
        else
        {
            (void)printf("couldn't find item\n");
            (void)sleep(2);
        }
    }
}
void view_payments(void)
{
}
void search_records(void)
{
}
void delete_records(void)
{
}