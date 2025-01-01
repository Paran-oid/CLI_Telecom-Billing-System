#include "billing.h"
#include "fileIO.h"
#include "record.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(__linux__)
#include <unistd.h>
#elif defined(__WIN32) || defined(__WIN64)
#include <windows.h>
#endif

const char *types[] = {"SMR", "CAR", "DTU", "SUB", "TAX", "PAY"};
size_t n = sizeof(types) / sizeof(types[0]);

void display_types(void) {
  for (size_t i = 0; i < n; i++) {
    (void)printf("%s ", (const char *)types[i]);
  }
  (void)printf("\n");
}

void add_record(const char *working_dir) {
  assert(working_dir);
  (void)srand(time(NULL));

  char output[100];
  struct Record rec;
  bool success = false;
  bool valid_id = false;
  int offset = 0;

  char rec_id_str[3];
  char rec_value_str[10];

  // check if generated ID for TRANSC is valid
  while (!valid_id) {
    rec.id = 1 + offset;
    (void)snprintf(rec_id_str, sizeof(rec_id_str), "%d", rec.id);
    char *found_item = (char *)search_in_file(working_dir, ID, rec_id_str);

    if (found_item == NULL) {
      valid_id = true;
    }
    offset++;
  }

  (void)strcat(output, rec_id_str);
  (void)printf("Enter value\n");
  if ((int)scanf("%f", &rec.val) == 1) {
    (void)snprintf(rec_value_str, sizeof(rec_value_str), "%.2f", rec.val);
    (void)strcat(output, " ");
    (void)strcat(output, rec_value_str);

    char input_type[3];
    (void)printf("Enter one of the following types:\n");
    (void)display_types();

    if (((int)scanf("%s", input_type) == 1)) {
      for (size_t i = 0; i < n; i++) {
        if ((int)strcmp(input_type, types[i]) == 0) {
          (void)strcat(output, " ");
          (void)strcat(output, input_type);
          (void)strcat(output, "\n");
          rec.type = i;
          success = true;
          break;
        }
      }
    }

    fprintf(stderr, "Invalid type...\n");
  }

  if (success) {
    if ((bool)file_write(working_dir, output)) {
      (void)printf("Successfully added record!\n");
    } else {
      (void)fprintf(stderr, "There was an error adding the record\n");
    }
  } else {
    (void)fprintf(stderr, "Please verify your inputs\n");
  }
}

void view_records(const char *working_dir) {
  assert(working_dir);
  char temp;
  (void)file_read(working_dir);
  (void)printf("Enter anything to continue...\n");
  (void)scanf(" %c", &temp);
}

void modify_records(const char *working_dir) {
  assert(working_dir);

  int transc_id;
  char transc_id_str[100];
  char *found_item = NULL;

  (void)printf("Enter item ID\n");
  if ((int)scanf(" %d", &transc_id) == 1) {
    (void)snprintf(transc_id_str, sizeof(transc_id), "%d", transc_id);
    found_item = (char *)search_in_file(working_dir, ID, transc_id_str);
    if (!(found_item == NULL)) {
      float new_item_val = 0.00f;
      char new_item_val_str[50];
      char new_item_type[3];

      (void)printf("Enter new value\n");
      (void)scanf("%f", &new_item_val);
      (void)snprintf(new_item_val_str, sizeof(new_item_val_str), "%.2f",
                     new_item_val);
      (void)printf("Enter new type (must be one of these)\n");
      (void)display_types();
      if (((int)scanf("%3s", new_item_type) == 1)) {
        bool found = false;
        while (!found) {
          for (size_t i = 0; i < n; i++) {
            if (strcmp(types[i], new_item_type) == 0) {
              found = true;
              break;
            }
          }
          if (!found) {
            fprintf(stderr,
                    "Couldn't find item type :/\n Please enter a valid type\n");
            (void)scanf("%3s", new_item_type);
          }
        }

        char modified_transc[150];
        char *building_strs[] = {transc_id_str, " ",           new_item_val_str,
                                 " ",           new_item_type, "\n",
                                 NULL};
        for (size_t i = 0; building_strs[i] != NULL; i++) {
          (void)strcat(modified_transc, building_strs[i]);
        }

        if ((bool)replace_in_file(working_dir, modified_transc, false)) {
          (void)printf("Success!\n");
          (void)sleep(2);
        }

        (void)free(found_item);
      }
    } else {
      fprintf(stderr, "Couldn't find item\n");
      (void)sleep(2);
    }
  }
}

void view_payments(const char *working_dir) {
  assert(working_dir);

  char c;
  (void)file_read(working_dir);
  (void)printf("Enter any key to continue\n");
  (void)scanf(" %c", &c);
}

void search_records(const char *working_dir) {
  assert(working_dir);

  int id;
  char id_str[3];
  (void)printf("Enter item id: \n");
  if ((int)scanf("%d", &id) == 1) {
    (void)snprintf(id_str, sizeof(id_str), "%d", id);
    char *transc = (char *)search_in_file(working_dir, ID, id_str);
    if (transc) {
      (void)printf("%s\n", transc);
      (void)free(transc);

      char c;
      (void)printf("Enter any key to continue\n");
      (void)scanf(" %c", &c);
    } else {
      fprintf(stderr, "Sorry couldn't find an entity with that id\n");
      sleep(2);
    }
  }
}

void delete_records(const char *working_dir) {
  assert(working_dir);

  int id;
  char id_str[3];
  (void)printf("Enter item id: \n");
  if ((int)scanf("%d", &id) == 1) {
    (void)snprintf(id_str, sizeof(id_str), "%d", id);
    char *transc = (char *)search_in_file(working_dir, ID, id_str);
    if (transc) {
      bool res = (bool)replace_in_file(working_dir, transc, true);
      (void)free(transc);
      if (res) {
        (void)printf("Success!\n");
      } else {
        fprintf(stderr, "Failure...\n");
      }
    } else {
      fprintf(stderr, "Sorry couldn't find an entity with that id\n");
    }
    sleep(2);
  }
}