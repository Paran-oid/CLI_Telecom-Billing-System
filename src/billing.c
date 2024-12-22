#include "billing.h"
#include "record.h"
#include "fileIO.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

void add_record(void)
{
    srand(time(NULL));

    char *types[] = {"SMR", "CAR", "DTU", "SUB", "TAX", "PAY"};
    size_t n = sizeof(types) / sizeof(types[0]);

    char output[100];
    struct Record rec;
    bool success = false;

    char rec_id_str[3];
    char rec_value_str[10];

    rec.id = 1 + (rand() % (100));

    snprintf(rec_id_str, sizeof(rec_id_str), "%d", rec.id);
    strcat(output,rec_id_str);
    
    printf("Enter value\n");
    if(scanf("%f",&rec.val) == 1)
    {
        snprintf(rec_value_str, sizeof(rec_value_str), "%.2f", rec.val);
        strcat(output, " ");
        strcat(output, rec_value_str);

        char input_type[3];
        printf("Enter one of the following types:\n");
        for(size_t i = 0; i < n; i++)
        {
            printf("%s ", types[i]);
        }
        printf("\n");

        if(scanf("%s", input_type) == 1)
        {
            for(size_t i = 0; i < n; i++)
            {
                if(strcmp(input_type,types[i]) == 0)
                {
                    strcat(output, " ");
                    strcat(output, input_type);
                    strcat(output, "\n");
                    rec.type = i;
                    success = true;
                    break;
                }
            }
        }
    }

    if(success)
    {
        printf("entered to success section \n");
        char *path = "../data/users/aziz_records.txt";
        if(file_write(path, output))
        {
            printf("Successfully added record!\n");
        } else {
            printf("There was an error adding the record\n");
        }
    } else {
        printf("Please verify your inputs next time\n");
    }
}
void view_records(void)
{

}
void modify_records(void)
{

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