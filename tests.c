#include "tests.h"
#include "program.h"
#include "user.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

const char *path = "../test-instructions.txt";

// create a fake user, return success if created then delete the temp user

void clone_user(void) {

  bool result;
  struct User *cloneUser = malloc(sizeof(struct User));
  struct User expectedUser = {99, "mega", "mega"};

  FILE *inputFile = fopen(path, "r");
  if (!inputFile) {
    perror("error opening file\n");
  }

  freopen("input.txt", "r", stdin);
  result = auth_handler(&cloneUser);

  printf("received user is %s\n", cloneUser->name);
  assert(result);
  assert(expectedUser.name == cloneUser->name);
  printf("user is %s\n", cloneUser->name);
}

void run_tests(void) { clone_user(); }